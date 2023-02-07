/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 14:21:07 by sbos          #+#    #+#                 */
/*   Updated: 2023/02/06 19:07:39 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "init/parse/rt_parse.h"
#include "debug/rt_debug.h"

static void	rt_key_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(data->mlx);
}

t_ray	create_ray(uint32_t x, uint32_t y, t_data *data)
{
	t_vector abs_up = (t_vector){.x = 0.0f, .y = 1.0f, .z = 0.0f};
	t_vector rel_forward = data->camera->orientation;
	t_vector rel_right = rt_normalized(rt_cross(rel_forward, abs_up));
	t_vector rel_up = rt_cross(rel_right, rel_forward);

	float half_fov_rad = data->camera->fov / 360 * (float)M_PI;
	float screen_width = fabsf(-2 * sinf(half_fov_rad) / cosf(half_fov_rad)); // fov / 2 (doe in radians)

	float dist_per_pix = screen_width / WINDOW_WIDTH;
	float screen_height = dist_per_pix * WINDOW_HEIGHT;

	t_vector leftward = rt_add(rt_scale(rel_right, -screen_width / 2), rel_forward);
	t_vector upward = rt_add(rt_scale(rel_up, screen_height / 2), rel_forward);

	t_vector top_left = rt_add(leftward, upward);
	t_vector pixel_coord = rt_add(rt_add(top_left, rt_scale(rel_right, x * dist_per_pix)), rt_scale(rel_up, y * -dist_per_pix));

	t_vector dir = rt_normalized(pixel_coord);
	t_vector origin = data->camera->coordinates;

	return ((t_ray){.direction = dir, .origin = origin});
}

uint32_t convert_color(t_rgb rgb)
{
	const uint32_t	r = (uint32_t)(rgb.r * 255);
	const uint32_t	g = (uint32_t)(rgb.g * 255);
	const uint32_t	b = (uint32_t)(rgb.b * 255);

	return ((r << 24) | (g << 16) | (b << 8) | 255);
}

void	rt_draw_loop(void *param)
{
	t_data *const	data = param;
	t_rgb			rgb;
	t_ray			ray;
	uint32_t		y;
	uint32_t		x;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			ray = create_ray(x, y, data);
			rgb = rt_get_ray_rgb(ray, data);
			mlx_put_pixel(data->image, x, y, convert_color(rgb));
			x++;
		}
		y++;
	}
}

static t_object	*rt_get_object_ptr(t_object_type searched_object_type,
					t_object *objects)
{
	size_t	object_index;
	size_t	size;

	object_index = 0;
	size = ft_vector_get_size(objects);
	while (object_index < size)
	{
		if (objects[object_index].type == searched_object_type)
			return (&objects[object_index]);
		object_index++;
	}
	return (NULL);
}

static void	rt_assign_capitalized_objects(t_data *data)
{
	data->ambient
		= &rt_get_object_ptr(OBJECT_TYPE_AMBIENT, data->objects)->ambient;
	data->camera
		= &rt_get_object_ptr(OBJECT_TYPE_CAMERA, data->objects)->camera;
	data->light
		= &rt_get_object_ptr(OBJECT_TYPE_LIGHT, data->objects)->light;
}

t_status	rt_init(int argc, char *argv[], t_data *data)
{
	ft_bzero(data, sizeof(*data));
	if (argc != 2)
		return (rt_print_error(ERROR_INVALID_ARGC));
	if (rt_parse_argv(argv, data) == ERROR)
		return (ERROR);
	rt_assign_capitalized_objects(data);
	rt_debug_print_objects(data);
	data->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, false);
	if (data->mlx == NULL || !mlx_loop_hook(data->mlx, &rt_draw_loop, data))
		return (rt_print_error(ERROR_SYSTEM));
	mlx_key_hook(data->mlx, &rt_key_hook, data);
	return (OK);
}
