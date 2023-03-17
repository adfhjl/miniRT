/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/16 18:21:47 by sbos          #+#    #+#                 */
/*   Updated: 2023/02/22 17:22:05 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rt_structs.h"

#include "draw/rt_draw.h"
#include "tracing/rt_tracing.h"
#include "utils/rt_utils.h"

static bool	rt_any_movement_key_pressed(t_held held)
{
	return (held.w_held
		|| held.a_held
		|| held.s_held
		|| held.d_held
		|| held.space_held
		|| held.shift_held);
}

static void	rt_move_camera_pos(t_data *data, t_vector direction,
				float delta_movement)
{
	t_ray	direction_ray;

	direction_ray = rt_get_ray(data->camera->pos, direction);
	data->camera->pos = rt_get_ray_endpoint(direction_ray, delta_movement);
}

static void	rt_update_camera_pos(t_data *data)
{
	float	delta_movement;

	delta_movement = data->movement_speed * (float)data->mlx->delta_time;
	if (data->held.w_held)
		rt_move_camera_pos(data, data->canvas.camera_forward, delta_movement);
	if (data->held.a_held)
		rt_move_camera_pos(data, data->canvas.camera_right, -delta_movement);
	if (data->held.s_held)
		rt_move_camera_pos(data, data->canvas.camera_forward, -delta_movement);
	if (data->held.d_held)
		rt_move_camera_pos(data, data->canvas.camera_right, delta_movement);
	if (data->held.space_held)
		rt_move_camera_pos(data, data->world_up, delta_movement);
	if (data->held.shift_held)
		rt_move_camera_pos(data, data->world_up, -delta_movement);
}

void	rt_draw_loop(void *param)
{
	t_data *const	data = param;

	if (!data->frozen)
	{
		if (rt_any_movement_key_pressed(data->held) || data->moved_cursor)
		{
			rt_reset_canvas_info(data);
		}
		data->moved_cursor = false;
		mlx_set_mouse_pos(data->mlx,
			data->scaled_window_center_x, data->scaled_window_center_y);
		rt_update_camera_pos(data);
	}
	rt_shoot_rays(data);
	if (rt_draw_debug_lines(data) == ERROR)
		mlx_close_window(data->mlx);
	data->seconds_ran += data->mlx->delta_time;
}
