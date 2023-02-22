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

#include "minirt.h"

#include "draw/rt_draw.h"
#include "debug/rt_debug.h"
#include "rays/rt_rays.h"

static bool	rt_any_movement_key_pressed(t_data *data)
{
	return (data->w_held
		|| data->a_held
		|| data->s_held
		|| data->d_held
		|| data->space_held
		|| data->shift_held);
}

static void	rt_update_camera_origin(t_data *data)
{
	float	delta_move;

	delta_move = data->movement_speed * (float)data->mlx->delta_time;
	if (data->w_held)
		data->camera->origin = rt_get_ray_point(rt_get_ray(data->camera->origin, data->camera_forward), delta_move);
	if (data->a_held)
		data->camera->origin = rt_get_ray_point(rt_get_ray(data->camera->origin, data->camera_right), -delta_move);
	if (data->s_held)
		data->camera->origin = rt_get_ray_point(rt_get_ray(data->camera->origin, data->camera_forward), -delta_move);
	if (data->d_held)
		data->camera->origin = rt_get_ray_point(rt_get_ray(data->camera->origin, data->camera_right), delta_move);
	if (data->space_held)
		data->camera->origin = rt_get_ray_point(rt_get_ray(data->camera->origin, data->world_up), delta_move);
	if (data->shift_held)
		data->camera->origin = rt_get_ray_point(rt_get_ray(data->camera->origin, data->world_up), -delta_move);
}

void	rt_draw_loop(void *param)
{
	t_data *const	data = param;

	if (data->cursor_frozen)
		return ;

	if (rt_any_movement_key_pressed(data) || data->moved_cursor)
		rt_reset_canvas_info(data);
	data->moved_cursor = false;

	mlx_set_mouse_pos(data->mlx, data->scaled_window_center_x, data->scaled_window_center_y);

	if (data->camera != NULL)
	{
		rt_update_camera_origin(data);
		rt_generate_noise(data);
		rt_shoot_rays(data);
	}

	if (rt_draw_debug_lines(data) == ERROR)
		mlx_close_window(data->mlx);
}
