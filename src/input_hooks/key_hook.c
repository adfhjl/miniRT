/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_hook.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/17 14:39:20 by sbos          #+#    #+#                 */
/*   Updated: 2023/02/23 17:49:52 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft/src/allocating/ft_allocating.h"

#include "rt_structs.h"

#include "draw/rt_draw.h"
#include "print/rt_print.h"

static void	rt_key_press_draw_mode(keys_t key, t_data *data)
{
	if (key == MLX_KEY_N)
	{
		data->draw_mode = DRAW_MODE_NORMAL;
		data->pixel_index = 0;
	}
	if (key == MLX_KEY_B)
	{
		data->draw_mode = DRAW_MODE_NOISE;
		data->pixel_index = 0;
	}
}

static void	rt_key_press_frozen(keys_t key, t_data *data)
{
	if (key == MLX_KEY_F)
	{
		data->frozen = !data->frozen;
		if (data->frozen)
			mlx_set_cursor_mode(data->mlx, MLX_MOUSE_NORMAL);
		else
			mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
	}
}

static void	rt_key_press_movement(keys_t key, t_data *data)
{
	if (key == MLX_KEY_W)
		data->held.w_held = true;
	if (key == MLX_KEY_A)
		data->held.a_held = true;
	if (key == MLX_KEY_S)
		data->held.s_held = true;
	if (key == MLX_KEY_D)
		data->held.d_held = true;
	if (key == MLX_KEY_SPACE)
		data->held.space_held = true;
	if (key == MLX_KEY_LEFT_SHIFT)
		data->held.shift_held = true;
}

static void	rt_key_release(keys_t key, t_data *data)
{
	if (key == MLX_KEY_W)
		data->held.w_held = false;
	if (key == MLX_KEY_A)
		data->held.a_held = false;
	if (key == MLX_KEY_S)
		data->held.s_held = false;
	if (key == MLX_KEY_D)
		data->held.d_held = false;
	if (key == MLX_KEY_SPACE)
		data->held.space_held = false;
	if (key == MLX_KEY_LEFT_SHIFT)
		data->held.shift_held = false;
}

void	rt_key_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.action == MLX_RELEASE)
		rt_key_release(keydata.key, data);
	else if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(data->mlx);
		rt_key_press_movement(keydata.key, data);
		if (keydata.key == MLX_KEY_G)
			data->draw_debug = !data->draw_debug;
		rt_key_press_frozen(keydata.key, data);
		rt_key_press_draw_mode(keydata.key, data);
		if (keydata.key == MLX_KEY_L)
			rt_print_scene(data);
		if (keydata.key == MLX_KEY_BACKSPACE)
			rt_reset_canvas_info(data);
		if (keydata.key == MLX_KEY_M)
			ft_print_allocations();
	}
}
