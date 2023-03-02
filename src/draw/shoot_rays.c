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

#include "minirt.h"

#include "draw/rt_draw.h"
#include "get_structs/rt_get_structs.h"
#include "rays/rt_rays.h"
#include "utils/rt_utils.h"
#include "vectors/rt_vectors.h"

static t_ray	rt_create_ray(float x, float y, t_data *data)
{
	t_vector	pixel_ray_x;
	t_vector	pixel_ray_y;
	t_vector	pixel_ray;
	t_vector	dir;

	pixel_ray_x = rt_scale(data->camera_right, x * data->dist_per_pix);
	pixel_ray_y = rt_scale(data->camera_up, y * -data->dist_per_pix);
	pixel_ray = rt_add(rt_add(data->canvas_top_left, pixel_ray_x), pixel_ray_y);
	dir = rt_normalized(pixel_ray);
	return (rt_get_ray(data->camera->pos, dir));
}

// Linear blend where an interpolation of 0.0f means old is returned,
// while 1.0f means new is returned.
static float	rt_lerp(float old, float new, float interpolation)
{
	return (old * (1 - interpolation) + new * interpolation);
}

static t_rgb	rt_shoot_ray(uint32_t x, uint32_t y, uint32_t location, t_data *data)
{
	t_ray	ray;
	t_rgb	rgb;

	ray = rt_create_ray(
		(rt_random_float_01() * 2.f - 1.f) * (float)AA_RADIUS + x,
		(rt_random_float_01() * 2.f - 1.f) * (float)AA_RADIUS + y,
		data);
	rgb = rt_get_ray_rgb(ray, data);

	rgb.r = rt_lerp(data->pixel_channel_floats[location * 4 + 0], rgb.r, 1.0f / (data->samples_since_last_movement + 1));
	rgb.g = rt_lerp(data->pixel_channel_floats[location * 4 + 1], rgb.g, 1.0f / (data->samples_since_last_movement + 1));
	rgb.b = rt_lerp(data->pixel_channel_floats[location * 4 + 2], rgb.b, 1.0f / (data->samples_since_last_movement + 1));

	data->pixel_channel_floats[location * 4 + 0] = rgb.r;
	data->pixel_channel_floats[location * 4 + 1] = rgb.g;
	data->pixel_channel_floats[location * 4 + 2] = rgb.b;

	return (rgb);
}

// static void	rt_shoot_voronoi_ray(t_data *data)
// {
// 	uint32_t	location;
// 	uint32_t	x;
// 	uint32_t	y;
// 	t_rgb		rgb;

// 	data->pixel_index--;
// 	location = data->available[data->pixel_index];
// 	x = location % UNSCALED_WINDOW_WIDTH;
// 	y = location / UNSCALED_WINDOW_WIDTH;
// 	rgb = rt_shoot_ray(x, y, data);
// 	rt_voronoi_floodfill((int32_t)x, (int32_t)y, rgb, data);
// }

// static void	rt_shoot_blue_noise_ray(t_data *data)
// {
// 	uint32_t	location;
// 	uint32_t	x;
// 	uint32_t	y;
// 	t_rgb		rgb;

// 	data->pixel_index--;
// 	location = data->available[data->pixel_index];
// 	x = location % UNSCALED_WINDOW_WIDTH;
// 	y = location / UNSCALED_WINDOW_WIDTH;
// 	rgb = rt_shoot_ray(x, y, data);
// 	rt_put_rgb(data->image, x, y, rgb);
// }

static void	rt_shoot_normal_ray(t_data *data)
{
	uint32_t	location;
	uint32_t	x;
	uint32_t	y;
	t_rgb		rgb;

	location = data->pixel_index;
	x = location % UNSCALED_WINDOW_WIDTH;
	y = location / UNSCALED_WINDOW_WIDTH;
	rgb = rt_shoot_ray(x, y, location, data);
	if (!data->frozen)
		rt_put_rgb(data->image, x, y, rgb);
}

void	rt_shoot_rays(t_data *data)
{
	size_t		ray_index;

	ray_index = 0;
	// TODO: Maybe don't stop drawing in DRAW_MODE_NORMAL until the frame has been completely drawn, no matter what?
	while (ray_index < RAYS_PER_FRAME)
	{
		// if (data->draw_mode == DRAW_MODE_VORONOI)
		// {
		// 	if (data->pixel_index <= data->available_count)
		// 		return ;
		// 	rt_shoot_voronoi_ray(data);
		// }
		// else if (data->draw_mode == DRAW_MODE_BLUE_NOISE)
		// {
		// 	if (data->pixel_index <= data->available_count)
		// 		return ;
		// 	rt_shoot_blue_noise_ray(data);
		// }
		// else if (data->draw_mode == DRAW_MODE_NORMAL)
		if (data->draw_mode == DRAW_MODE_NORMAL)
		{
			rt_shoot_normal_ray(data);
		}
		if (data->pixel_index + 1 == data->pixel_count)
			data->samples_since_last_movement++;
		data->pixel_index = (data->pixel_index + 1) % data->pixel_count;
		ray_index++;
	}
}
