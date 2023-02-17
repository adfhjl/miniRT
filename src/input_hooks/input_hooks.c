/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_hooks.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/17 14:39:20 by sbos          #+#    #+#                 */
/*   Updated: 2023/02/17 14:39:20 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mathematics/utils/rt_mathematics_utils.h"

void	rt_key_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;

	if (keydata.action == MLX_RELEASE)
	{
		if (keydata.key == MLX_KEY_W)
			data->w_held = false;
		if (keydata.key == MLX_KEY_A)
			data->a_held = false;
		if (keydata.key == MLX_KEY_S)
			data->s_held = false;
		if (keydata.key == MLX_KEY_D)
			data->d_held = false;
		if (keydata.key == MLX_KEY_SPACE)
			data->space_held = false;
		if (keydata.key == MLX_KEY_LEFT_SHIFT)
			data->shift_held = false;
	}
	else if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(data->mlx);

		if (keydata.key == MLX_KEY_G)
			data->draw_debug = !data->draw_debug;

		if (keydata.key == MLX_KEY_W)
			data->w_held = true;
		if (keydata.key == MLX_KEY_A)
			data->a_held = true;
		if (keydata.key == MLX_KEY_S)
			data->s_held = true;
		if (keydata.key == MLX_KEY_D)
			data->d_held = true;
		if (keydata.key == MLX_KEY_SPACE)
			data->space_held = true;
		if (keydata.key == MLX_KEY_LEFT_SHIFT)
			data->shift_held = true;
	}
}

void	rt_cursor_hook(double xpos, double ypos, void* param)
{
	t_data	*data;
	float	dx;
	float	dy;

	data = param;
	dx = (float)xpos - data->window_center_x;
	dy = -((float)ypos - data->window_center_y);

	const float	delta_cursor_move = ROTATION_FACTOR * (float)data->mlx->delta_time;

	t_vector	rotation_right;
	rotation_right = rt_scale(data->camera_right, (float)dx * delta_cursor_move);
	t_vector	rotation_up;
	rotation_up = rt_scale(data->camera_up, (float)dy * delta_cursor_move);

	t_vector	rotation;
	rotation = rt_add(rotation_right, rotation_up);

	// TODO: This may feel better when used in the rt_add() statement below.
	// t_vector	offet_rotation;
	// offet_rotation = rt_add(data->camera->normal, rotation);

	data->camera->normal = rt_normalized(rt_add(data->camera->normal, rotation));

	data->moved_cursor = true;
}
