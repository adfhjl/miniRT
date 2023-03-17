/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_hooks.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/17 14:39:20 by sbos          #+#    #+#                 */
/*   Updated: 2023/02/23 17:49:52 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rt_structs.h"

#include "debug/rt_debug.h" // TODO: REMOVE
#include "draw/rt_draw.h"
#include "vectors/rt_vectors.h"

void	rt_key_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;

	if (keydata.action == MLX_RELEASE)
	{
		if (keydata.key == MLX_KEY_W)
			data->held.w_held = false;
		if (keydata.key == MLX_KEY_A)
			data->held.a_held = false;
		if (keydata.key == MLX_KEY_S)
			data->held.s_held = false;
		if (keydata.key == MLX_KEY_D)
			data->held.d_held = false;
		if (keydata.key == MLX_KEY_SPACE)
			data->held.space_held = false;
		if (keydata.key == MLX_KEY_LEFT_SHIFT)
			data->held.shift_held = false;
	}
	else if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(data->mlx);

		if (keydata.key == MLX_KEY_W)
			data->held.w_held = true;
		if (keydata.key == MLX_KEY_A)
			data->held.a_held = true;
		if (keydata.key == MLX_KEY_S)
			data->held.s_held = true;
		if (keydata.key == MLX_KEY_D)
			data->held.d_held = true;
		if (keydata.key == MLX_KEY_SPACE)
			data->held.space_held = true;
		if (keydata.key == MLX_KEY_LEFT_SHIFT)
			data->held.shift_held = true;

		if (keydata.key == MLX_KEY_G)
			data->draw_debug = !data->draw_debug;

		if (keydata.key == MLX_KEY_F)
		{
			data->frozen = !data->frozen;
			if (data->frozen)
				mlx_set_cursor_mode(data->mlx, MLX_MOUSE_NORMAL);
			else
				mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
		}

		if (keydata.key == MLX_KEY_N)
		{
			data->draw_mode = DRAW_MODE_NORMAL;
			data->pixel_index = 0;
		}
		if (keydata.key == MLX_KEY_B)
		{
			data->draw_mode = DRAW_MODE_NOISE;
			data->pixel_index = 0;
		}

		if (keydata.key == MLX_KEY_L)
			rt_print_scene(data);

		if (keydata.key == MLX_KEY_BACKSPACE)
			rt_reset_canvas_info(data);
	}
}

void	rt_cursor_hook(double x, double y, void *param)
{
	t_data		*data;
	float		dx;
	float		dy;
	t_vector	rotation_right;
	t_vector	rotation_up;
	t_vector	rotation;

	data = param;
	if (data->frozen)
		return ;
	dx = (float)x - data->scaled_window_center_x;
	dy = -((float)y - data->scaled_window_center_y);
	rotation_right = rt_scale(data->canvas.camera_right, (float)dx * ROTATION_SPEED);
	rotation_up = rt_scale(data->canvas.camera_up, (float)dy * ROTATION_SPEED);
	rotation = rt_add(rotation_right, rotation_up);
	data->camera->normal = rt_normalized(rt_add(data->camera->normal, rotation));
	rt_assert_normal(data->camera->normal, "d");
	data->moved_cursor = true;
}

void	rt_scroll_hook(double dx, double dy, void *param)
{
	t_data	*data;

	(void)dx;
	data = param;
	if (dy > 0)
	{
		data->camera->fov *= 0.8f;
		rt_reset_canvas_info(data);
	}
	if (dy < 0 && data->camera->fov < 180.f * 0.8f)
	{
		data->camera->fov /= 0.8f;
		rt_reset_canvas_info(data);
	}
}
