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

#include "rt_structs.h"

#include "draw/rt_draw.h"
#include "init/parse/rt_parse.h"
#include "init/rt_init.h"
#include "input_hooks/rt_input_hooks.h"
#include "utils/rt_utils.h"
#include "vectors/rt_vectors.h"

#include <math.h>

static void	rt_init_noise_indices(t_data *data)
{
	uint32_t	index;

	index = 0;
	while (index < data->pixel_count)
	{
		data->noise_indices[index] = index;
		index++;
	}
	rt_shuffle(data->noise_indices, data->pixel_count);
}

static bool	rt_camera_is_invalid(t_data *data)
{
	data->canvas.camera_right = rt_normalized(
			rt_cross(data->camera->normal, data->world_up));
	if (isnan(data->canvas.camera_right.x)
		|| isnan(data->canvas.camera_right.y)
		|| isnan(data->canvas.camera_right.z))
		return (true);
	return (data->camera
		&& data->camera->normal.x == 0
		&& data->camera->normal.z == 0);
}

static void	rt_init_constants(t_data *data)
{
	data->world_up = (t_vector){0, 1, 0};
	data->scaled_window_width = UNSCALED_WINDOW_WIDTH * PIXEL_SCALE;
	data->scaled_window_height = UNSCALED_WINDOW_HEIGHT * PIXEL_SCALE;
	data->scaled_window_center_x = data->scaled_window_width / 2;
	data->scaled_window_center_y = data->scaled_window_height / 2;
	data->pixel_count = UNSCALED_WINDOW_WIDTH * UNSCALED_WINDOW_HEIGHT;
	data->movement_speed = MOVEMENT_SPEED;
	data->draw_debug = DEBUG_DRAW_ON_BY_DEFAULT;
	data->draw_mode = DEFAULT_DRAW_MODE;
}

static void	rt_init_hooks(t_data *data)
{
	mlx_key_hook(data->mlx, &rt_key_hook, data);
	mlx_cursor_hook(data->mlx, &rt_cursor_hook, data);
	mlx_scroll_hook(data->mlx, &rt_scroll_hook, data);
}

t_status	rt_init(int argc, char *argv[], t_data *data)
{
	if (argc != 2)
		return (rt_print_error(ERROR_INVALID_ARGC));
	if (rt_parse_argv(argv, data) == ERROR)
		return (ERROR);
	rt_assign_capitalized_objects(data);
	rt_init_constants(data);
	rt_init_noise_indices(data);
	if (rt_camera_is_invalid(data))
		return (rt_print_error(ERROR_INVALID_CAMERA_DIR));
	data->mlx = mlx_init(data->scaled_window_width, data->scaled_window_height,
			WINDOW_TITLE, false);
	if (data->mlx == NULL || !mlx_loop_hook(data->mlx, &rt_draw_loop, data))
		return (rt_print_error(ERROR_MLX));
	rt_init_hooks(data);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
	data->image = mlx_new_image(data->mlx, (uint32_t)data->scaled_window_width,
			(uint32_t)data->scaled_window_height);
	if (data->image == NULL)
		return (rt_print_error(ERROR_MLX));
	if (mlx_image_to_window(data->mlx, data->image, 0, 0) < 0)
		return (rt_print_error(ERROR_MLX));
	rt_reset_canvas_info(data);
	return (OK);
}
