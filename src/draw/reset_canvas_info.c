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

#include "rt_structs.h"

#include "draw/rt_draw.h"
#include "tracing/rt_tracing.h"
#include "vectors/rt_vectors.h"

#include <assert.h> // TODO: REMOVE
#include <math.h> // TODO: REMOVE

static t_vector	rt_get_canvas_top_left(float canvas_width, t_canvas canvas,
					t_vector camera_dir)
{
	t_vector	left_canvas_side;
	float		canvas_height;
	t_vector	top_canvas_side;

	left_canvas_side = rt_scale(canvas.camera_right, -canvas_width / 2);
	canvas_height = canvas.distance_per_pixel * UNSCALED_WINDOW_HEIGHT;
	top_canvas_side = rt_scale(canvas.camera_up, canvas_height / 2);
	return (rt_add(rt_add(left_canvas_side, top_canvas_side), camera_dir));
}

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
static void	rt_update_canvas_info(t_data *data)
{
	t_vector	camera_dir;
	t_canvas	*canvas;
	float		half_fov_rad;
	float		canvas_width;

	camera_dir = data->camera->normal;
	canvas = &data->canvas;
	canvas->camera_right = rt_normalized(rt_cross(camera_dir, data->world_up));
	assert(!isnan(canvas->camera_right.x) && !isnan(canvas->camera_right.y) && !isnan(canvas->camera_right.z));
	canvas->camera_forward = rt_cross(data->world_up, canvas->camera_right);
	canvas->camera_up = rt_cross(canvas->camera_right, camera_dir);
	assert(!isnan(canvas->camera_up.x) && !isnan(canvas->camera_up.y) && !isnan(canvas->camera_up.z));
	half_fov_rad = data->camera->fov / 2 * ((float)M_PI / 180);
	canvas_width = fabsf(-2 * tanf(half_fov_rad));
	canvas->distance_per_pixel = canvas_width / UNSCALED_WINDOW_WIDTH;
	canvas->top_left = rt_get_canvas_top_left(
			canvas_width, *canvas, camera_dir);
}

static void	rt_clear_image(mlx_image_t *image)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	color;

	color = rt_convert_color((t_rgb){UNRENDERED_R, UNRENDERED_G, UNRENDERED_B});
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

void	rt_reset_canvas_info(t_data *data)
{
	rt_update_canvas_info(data);
	rt_clear_image(data->image);
	data->pixel_index = 0;
	data->samples_since_last_movement = 0;
}
