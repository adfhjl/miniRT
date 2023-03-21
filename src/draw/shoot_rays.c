/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shoot_rays.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/16 18:21:24 by sbos          #+#    #+#                 */
/*   Updated: 2023/02/23 17:57:01 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rt_structs.h"

#include "draw/rt_draw.h"
#include "tracing/rt_tracing.h"
#include "utils/rt_utils.h"
#include "vectors/rt_vectors.h"

static t_ray	rt_create_ray(float x, float y, t_data *data)
{
	t_vector	pixel_ray_x;
	t_vector	pixel_ray_y;
	t_vector	pixel_ray;
	t_vector	dir;

	pixel_ray_x = rt_scale(data->canvas.camera_right,
			x * data->canvas.distance_per_pixel);
	pixel_ray_y = rt_scale(data->canvas.camera_up,
			y * -data->canvas.distance_per_pixel);
	pixel_ray = rt_add(rt_add(data->canvas.top_left, pixel_ray_x), pixel_ray_y);
	dir = rt_normalized(pixel_ray);
	return (rt_get_ray(data->camera->pos, dir));
}

// Linear blend where an interpolation of 0.0 means old is returned,
// while 1.0 means new_ is returned.
static double	rt_lerp_double(double old, double new_, double t)
{
	return (old * (1 - t) + new_ * t);
}

static void	rt_lerp_channel(uint32_t location, uint32_t channel_offset,
				float channel, t_data *data)
{
	uint32_t	channel_location;
	double		*channel_double;
	double		t;

	channel_location = location * 4 + channel_offset;
	channel_double = &data->pixel_channel_doubles[channel_location];
	t = 1.0 / (data->samples_since_last_movement + 1);
	*channel_double = rt_lerp_double(*channel_double, (double)channel, t);
}

static t_rgb	rt_shoot_ray(uint32_t x, uint32_t y, uint32_t location,
					t_data *data)
{
	float	dx;
	float	dy;
	t_ray	ray;
	t_rgb	rgb;

	dx = rt_random_float_01() * 2.f - 1.f;
	dy = rt_random_float_01() * 2.f - 1.f;
	ray = rt_create_ray(dx * ANTI_ALIAS_RADIUS + x, dy * ANTI_ALIAS_RADIUS + y,
			data);
	rgb = rt_trace(ray, data);
	rt_lerp_channel(location, 0, rgb.r, data);
	rt_lerp_channel(location, 1, rgb.g, data);
	rt_lerp_channel(location, 2, rgb.b, data);
	rgb.r = (float)data->pixel_channel_doubles[location * 4 + 0];
	rgb.g = (float)data->pixel_channel_doubles[location * 4 + 1];
	rgb.b = (float)data->pixel_channel_doubles[location * 4 + 2];
	return (rgb);
}

void	rt_shoot_rays(t_data *data)
{
	size_t		ray_index;
	uint32_t	location;
	uint32_t	x;
	uint32_t	y;
	t_rgb		rgb;

	ray_index = 0;
	while (ray_index < RAYS_PER_FRAME)
	{
		location = data->pixel_index;
		if (data->draw_mode == DRAW_MODE_NOISE)
			location = data->noise_indices[data->pixel_index];
		x = location % UNSCALED_WINDOW_WIDTH;
		y = location / UNSCALED_WINDOW_WIDTH;
		rgb = rt_shoot_ray(x, y, location, data);
		if (!data->frozen)
			rt_put_rgb(data->image, x, y, rgb);
		if (data->pixel_index + 1 == data->pixel_count)
			data->samples_since_last_movement++;
		data->pixel_index = (data->pixel_index + 1) % data->pixel_count;
		ray_index++;
	}
}
