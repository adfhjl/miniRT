/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   scroll_hook.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 18:19:21 by sbos          #+#    #+#                 */
/*   Updated: 2023/03/17 18:19:21 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rt_structs.h"

#include "draw/rt_draw.h"

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
