/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reset_canvas_info.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/16 18:19:55 by sbos          #+#    #+#                 */
/*   Updated: 2023/02/22 17:23:22 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#include "draw/rt_draw.h"
#include "mathematics/rt_mathematics.h"
#include "rays/rt_rays.h"

// forward = (0, 0, 1);
//
// leftmost = (sin(-35o), 0, cos(-35o))
// rightmost = (sin(35o), 0, cos(35o))
// leftmost.xyz /= leftmost.z;
// rightmost.xyz /= rightmost.z;
//
// leftmost = (sin(-35o) / cos(-35o), 0 / cos(-35o), cos(-35o) / cos(-35o))
// rightmost = (sin(35o) / cos(35o), 0 / cos(35o), cos(35o) /cos(35o))
//
// leftmost = (-sin(35o) / cos(35o), 0, 1)
// rightmost = (sin(35o) / cos(35o), 0, 1)
//
// leftmost = (-tan(35o), 0, 1)
// rightmost = (tan(35o), 0, 1)
//
// width = abs(leftmost.x - rightmost.x);
//
// width = abs(-tan(35o) - tan(35o));
//
// tan(0) is 0, tan() until 90 degrees is positive, 90 is NAN (+-inf)
// width = abs(-2 * tan(35o));
// TODO: Call this every frame
static void	rt_update_canvas_info(t_data *data)
{
	t_vector	camera_normal;

	if (data->camera == NULL)
		return ;

	camera_normal = data->camera->normal;

	data->camera_right = rt_normalized(rt_cross(camera_normal, data->world_up));
	assert(!isnan(data->camera_right.x) && !isnan(data->camera_right.y) && !isnan(data->camera_right.z));

	data->camera_forward = rt_cross(data->world_up, data->camera_right);
	data->camera_up = rt_cross(data->camera_right, camera_normal);
	// TODO: If this assert is never ever triggered in any of the scenes, remove it
	assert(!isnan(data->camera_up.x) && !isnan(data->camera_up.y) && !isnan(data->camera_up.z));
	// if (isnan(data->camera_up.x) || isnan(data->camera_up.y) || isnan(data->camera_up.z))
	// 	return (ERROR);

	float half_fov_rad = data->camera->fov / 2 * ((float)M_PI / 180);
	float canvas_width = fabsf(-2 * tanf(half_fov_rad));
	data->dist_per_pix = canvas_width / UNSCALED_WINDOW_WIDTH;
	float canvas_height = data->dist_per_pix * UNSCALED_WINDOW_HEIGHT;
	t_vector left_canvas_side = rt_add(rt_scale(data->camera_right, -canvas_width / 2), camera_normal);
	t_vector top_canvas_side = rt_add(rt_scale(data->camera_up, canvas_height / 2), camera_normal);
	data->canvas_top_left = rt_add(left_canvas_side, top_canvas_side);
}

static void	rt_clear_image(mlx_image_t *image)
{
	uint32_t	x;
	uint32_t	y;
	t_rgb		unrendered_rgb;
	uint32_t	color;

	unrendered_rgb = (t_rgb){
		UNRENDERED_R / 255.f,
		UNRENDERED_G / 255.f,
		UNRENDERED_B / 255.f
	};
	color = rt_convert_color(unrendered_rgb);
	y = 0;
	while (y < UNSCALED_WINDOW_HEIGHT)
	{
		x = 0;
		while (x < UNSCALED_WINDOW_WIDTH)
		{
			rt_put_color(image, x, y, color);
			x++;
		}
		y++;
	}
}

static void	rt_reset_voronoi(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->pixel_count)
	{
		data->voronoi.distances[i] = UINT32_MAX;
		data->voronoi.visited[i] = false;
		i++;
	}
}

void	rt_reset_canvas_info(t_data *data)
{
	rt_update_canvas_info(data);
	if (data->draw_mode == DRAW_MODE_VORONOI)
	{
		rt_reset_voronoi(data);
	}
	else if (data->draw_mode == DRAW_MODE_BLUE_NOISE
		|| data->draw_mode == DRAW_MODE_NORMAL)
	{
		rt_clear_image(data->image);
	}
	data->pixel_index = data->pixel_count;
}
