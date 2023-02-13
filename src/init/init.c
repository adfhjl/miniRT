/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 14:21:07 by sbos          #+#    #+#                 */
/*   Updated: 2023/02/10 15:07:59 by vbenneko      ########   odam.nl         */
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

// forward = (0, 0, 1);
//
// leftmost = (sin(-35o), 0, cos(-35o))
// rightmost = (sin(35o), 0, cos(35o))
// leftmost.xyz /= leftmost.z;
// rightmost.xyz /= rightmost.z;
//
// leftmost = (sin(-35o) / cos(-35o), 0 / cos(-35o), cos(-35o) / cos(-35o))
// rightmost = (sin(35o) / cos(35o), 0 / cos(35o), cos(35o) /cos(35o))
//
// leftmost = (-sin(35o) / cos(35o), 0, 1)
// rightmost = (sin(35o) / cos(35o), 0, 1)
//
// leftmost = (-tan(35o), 0, 1)
// rightmost = (tan(35o), 0, 1)
//
// width = abs(leftmost.x - rightmost.x);
//
// width = abs(-tan(35o) - tan(35o));
//
// tan(0) is 0, tan() until 90 degrees is positive, 90 is NAN (+-inf)
// width = abs(-2 * tan(35o));
static t_ray	rt_create_ray(uint32_t x, uint32_t y, t_data *data)
{
	t_vector world_up = (t_vector){.x = 0.0f, .y = 1.0f, .z = 0.0f};
	t_vector cam_forward = data->camera->normal;
	t_vector cam_right = rt_normalized(rt_cross(cam_forward, world_up));
	assert(!isnan(cam_right.x) && !isnan(cam_right.y) && !isnan(cam_right.z));
	t_vector cam_up = rt_cross(cam_right, cam_forward);
	assert(!isnan(cam_up.x) && !isnan(cam_up.y) && !isnan(cam_up.z));

	float half_fov_rad = data->camera->fov / 2 * ((float)M_PI / 180);
	float canvas_width = fabsf(-2 * tanf(half_fov_rad));

	float dist_per_pix = canvas_width / WINDOW_WIDTH;
	float canvas_height = dist_per_pix * WINDOW_HEIGHT;

	t_vector left_canvas_side = rt_add(rt_scale(cam_right, -canvas_width / 2), cam_forward);
	t_vector top_canvas_side = rt_add(rt_scale(cam_up, canvas_height / 2), cam_forward);

	t_vector top_left = rt_add(left_canvas_side, top_canvas_side);
	t_vector pixel_coord = rt_add(rt_add(top_left, rt_scale(cam_right, x * dist_per_pix)), rt_scale(cam_up, y * -dist_per_pix));

	t_vector dir = rt_normalized(pixel_coord);
	t_vector origin = data->camera->origin;

	return (rt_get_ray(origin, dir));
}

static uint32_t rt_convert_color(t_rgb rgb)
{
	const uint32_t	r = (uint32_t)(rgb.r * 255);
	const uint32_t	g = (uint32_t)(rgb.g * 255);
	const uint32_t	b = (uint32_t)(rgb.b * 255);

	return ((r << 24) | (g << 16) | (b << 8) | 255);
}

static void	rt_draw_loop(void *param)
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
			ray = rt_create_ray(x, y, data); // TODO: Revamp this function to not recalculate stuff unnecesarally
			rgb = rt_get_ray_rgb(ray, data);
			mlx_put_pixel(data->image, x, y, rt_convert_color(rgb));
			x++;
		}
		y++;
	}
}

static bool	rt_camera_is_invalid(t_data *data)
{
	return (data->camera
	&& data->camera->normal.x == 0
	&& data->camera->normal.z == 0);
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
	if (rt_camera_is_invalid(data))
		return (rt_print_error(ERROR_INVALID_CAMERA_NORMAL));
	rt_debug_print_objects(data);
	data->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, false);
	if (data->mlx == NULL || !mlx_loop_hook(data->mlx, &rt_draw_loop, data))
		return (rt_print_error(ERROR_SYSTEM));
	mlx_key_hook(data->mlx, &rt_key_hook, data);
	return (OK);
}
