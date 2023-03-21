/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cursor_hook.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 18:19:08 by sbos          #+#    #+#                 */
/*   Updated: 2023/03/17 18:19:08 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rt_structs.h"

#include "vectors/rt_vectors.h"

static void	rt_update_camera_direction(float dx, float dy, t_data *data)
{
	t_vector	rotation_right;
	t_vector	rotation_up;
	t_vector	rotation;

	rotation_right = rt_scale(data->canvas.camera_right, dx * ROTATION_SPEED);
	rotation_up = rt_scale(data->canvas.camera_up, dy * ROTATION_SPEED);
	rotation = rt_add(rotation_right, rotation_up);
	data->camera->normal = rt_normalized(
			rt_add(data->camera->normal, rotation));
}

void	rt_cursor_hook(double x, double y, void *param)
{
	t_data	*data;
	float	dx;
	float	dy;

	data = param;
	if (data->frozen)
		return ;
	dx = (float)x - data->scaled_window_center_x;
	dy = -((float)y - data->scaled_window_center_y);
	rt_update_camera_direction(dx, dy, data);
	data->moved_cursor = true;
}
