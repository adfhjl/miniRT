/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 14:21:07 by sbos          #+#    #+#                 */
/*   Updated: 2023/02/22 15:58:46 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#include "draw/rt_draw.h"
#include "init/parse/rt_parse.h"
#include "input_hooks/rt_input_hooks.h"
#include "mathematics/rt_mathematics.h"

static void	rt_init_available(t_data *data)
{
	uint32_t	index;

	index = 0;
	while (index < data->pixel_count)
	{
		data->available[index] = index;
		data->densities[index] = 0;
		index++;
	}

	rt_shuffle(data->available, data->pixel_count);

	uint32_t	value;
	index = 0;
	while (index < data->pixel_count)
	{
		value = data->available[index];
		data->available_inverse[value] = index;
		index++;
	}
}

static t_status	rt_calloc_blue_noise_arrays(t_data *data)
{
	data->available = ft_calloc(data->pixel_count,
			sizeof(*data->available));
	data->available_inverse = ft_calloc(data->pixel_count,
			sizeof(*data->available_inverse));
	data->densities = ft_calloc(data->pixel_count,
			sizeof(*data->densities));
	if (data->available == NULL
		|| data->available_inverse == NULL
		|| data->densities == NULL)
		return (rt_print_error(ERROR_SYSTEM));
	return (OK);
}

static bool	rt_camera_is_invalid(t_data *data)
{
	if (data->camera == NULL)
		return (false);
	data->world_up = (t_vector){.x = 0.0f, .y = 1.0f, .z = 0.0f};
	data->camera_right = rt_normalized(rt_cross(data->camera->normal, data->world_up));
	if (isnan(data->camera_right.x) || isnan(data->camera_right.y) || isnan(data->camera_right.z))
		return (true);
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

	data->scaled_window_width = UNSCALED_WINDOW_WIDTH * PIXEL_SCALE;
	data->scaled_window_height = UNSCALED_WINDOW_HEIGHT * PIXEL_SCALE;

	data->scaled_window_center_x = data->scaled_window_width / 2;
	data->scaled_window_center_y = data->scaled_window_height / 2;

	data->pixel_count = UNSCALED_WINDOW_WIDTH * UNSCALED_WINDOW_HEIGHT;
	data->available_count = data->pixel_count;

	data->mlx = mlx_init(data->scaled_window_width, data->scaled_window_height, WINDOW_TITLE, false);
	if (data->mlx == NULL || !mlx_loop_hook(data->mlx, &rt_draw_loop, data))
		return (rt_print_error(ERROR_MLX));

	mlx_key_hook(data->mlx, &rt_key_hook, data);
	mlx_cursor_hook(data->mlx, &rt_cursor_hook, data);
	mlx_scroll_hook(data->mlx, &rt_scroll_hook, data);

	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);

	// TODO: Change the cursor to a hand when rotating any object but the camera
	// mlx_set_cursor

	data->image = mlx_new_image(data->mlx, (uint32_t)data->scaled_window_width, (uint32_t)data->scaled_window_height);
	if (data->image == NULL)
		return (rt_print_error(ERROR_MLX));

	int	instance_index;
	instance_index = mlx_image_to_window(data->mlx, data->image, 0, 0);
	if (instance_index < 0)
		return (rt_print_error(ERROR_MLX));

	data->movement_speed = MOVEMENT_SPEED;

	data->draw_debug = DEBUG_DRAW_ON_BY_DEFAULT;
	data->draw_mode = DEFAULT_DRAW_MODE;

	data->reflection_contribution = REFLECTION_CONTRIBUTION;

	data->voronoi.distances = ft_calloc(data->pixel_count, sizeof(*data->voronoi.distances));
	if (data->voronoi.distances == NULL)
		return (rt_print_error(ERROR_SYSTEM));

	// TODO: Make sure it isn't 2x necessary
	data->voronoi.stack = ft_vector_new_reserved(sizeof(*data->voronoi.stack), data->pixel_count);
	if (data->voronoi.stack == NULL)
		return (rt_print_error(ERROR_SYSTEM));

	data->voronoi.visited = ft_calloc(data->pixel_count, sizeof(*data->voronoi.visited));
	if (data->voronoi.visited == NULL)
		return (rt_print_error(ERROR_SYSTEM));

	if (rt_calloc_blue_noise_arrays(data) == ERROR)
		return (ERROR);

	rt_init_available(data);

	rt_reset_canvas_info(data);

	// SQRT2, because radius is circular.
	// It is the width/height multiplier necessary to reach the bottom-right
	// of the canvas starting from the top-left of the canvas.
	data->starting_update_radius = (uint32_t)fmaxf(UNSCALED_WINDOW_WIDTH * (float)M_SQRT2, UNSCALED_WINDOW_HEIGHT * (float)M_SQRT2);

	return (OK);
}
