/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reset_canvas_info.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/16 18:19:55 by sbos          #+#    #+#                 */
/*   Updated: 2023/02/16 18:19:55 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	const t_vector camera_forward = data->camera->normal;

	data->camera_right = rt_normalized(rt_cross(camera_forward, data->world_up));
	assert(!isnan(data->camera_right.x) && !isnan(data->camera_right.y) && !isnan(data->camera_right.z));

	data->camera_up = rt_cross(data->camera_right, camera_forward);
	// TODO: If this assert is never ever triggered in any of the scenes, remove it
	assert(!isnan(data->camera_up.x) && !isnan(data->camera_up.y) && !isnan(data->camera_up.z));
	// if (isnan(data->camera_up.x) || isnan(data->camera_up.y) || isnan(data->camera_up.z))
	// 	return (ERROR);

	float half_fov_rad = data->camera->fov / 2 * ((float)M_PI / 180);
	float canvas_width = fabsf(-2 * tanf(half_fov_rad));
	data->dist_per_pix = canvas_width / WINDOW_WIDTH;
	float canvas_height = data->dist_per_pix * WINDOW_HEIGHT;
	t_vector left_canvas_side = rt_add(rt_scale(data->camera_right, -canvas_width / 2), camera_forward);
	t_vector top_canvas_side = rt_add(rt_scale(data->camera_up, canvas_height / 2), camera_forward);
	data->canvas_top_left = rt_add(left_canvas_side, top_canvas_side);
}

static void	rt_clear_image(mlx_image_t *image)
{
	uint32_t	x;
	uint32_t	y;
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			mlx_put_pixel(image, x, y, (
					(uint32_t)UNRENDERED_R << 24)
				| ((uint32_t)UNRENDERED_G << 16)
				| ((uint32_t)UNRENDERED_B << 8)
				| 0xFF);
			x++;
		}
		y++;
	}
}

void	rt_reset_canvas_info(t_data *data)
{
	rt_update_canvas_info(data);
	rt_clear_image(data->image);
	data->pixel_index = data->pixel_count;
}
