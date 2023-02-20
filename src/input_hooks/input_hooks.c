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

#include "debug/rt_debug.h"
#include "draw/rt_draw.h"
#include "mathematics/rt_mathematics.h"

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

		if (keydata.key == MLX_KEY_G)
			data->draw_debug = !data->draw_debug;

		if (keydata.key == MLX_KEY_N)
		{
			data->draw_mode = DRAW_MODE_NORMAL;
			rt_reset_canvas_info(data);
		}
		if (keydata.key == MLX_KEY_B)
		{
			data->draw_mode = DRAW_MODE_BLUE_NOISE;
			rt_reset_canvas_info(data);
		}
		if (keydata.key == MLX_KEY_V)
		{
			data->draw_mode = DRAW_MODE_VORONOI;
			rt_reset_canvas_info(data);
		}

		if (keydata.key == MLX_KEY_L)
			rt_print_scene(data);
	}
}

void	rt_cursor_hook(double x, double y, void *param)
{
	t_data	*data;
	float	dx;
	float	dy;


	data = param;
	if (data->camera == NULL)
		return ;

	dx = (float)x - data->window_center_x;
	dy = -((float)y - data->window_center_y);

	t_vector	rotation_right;
	rotation_right = rt_scale(data->camera_right, (float)dx * ROTATION_SPEED);
	t_vector	rotation_up;
	rotation_up = rt_scale(data->camera_up, (float)dy * ROTATION_SPEED);

	t_vector	rotation;
	rotation = rt_add(rotation_right, rotation_up);

	// TODO: This may feel better when used in the rt_add() statement below.
	// t_vector	offet_rotation;
	// offet_rotation = rt_add(data->camera->normal, rotation);

	data->camera->normal = rt_normalized(rt_add(data->camera->normal, rotation));

	data->moved_cursor = true;
}

void	rt_scroll_hook(double dx, double dy, void *param)
{
	t_data	*data;

	(void)dx;
	data = param;
	if (dy > 0 && data->movement_speed < MAX_MOVEMENT_SPEED)
		data->movement_speed *= MOVEMENT_SPEED_SCROLL_FACTOR;
	else if (dy < 0 && data->movement_speed > MIN_MOVEMENT_SPEED)
		data->movement_speed /= MOVEMENT_SPEED_SCROLL_FACTOR;
}
