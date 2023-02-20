/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shoot_rays.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/16 18:21:24 by sbos          #+#    #+#                 */
/*   Updated: 2023/02/16 18:21:24 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#include "draw/rt_draw.h"
#include "mathematics/rt_mathematics.h"
#include "rays/rt_rays.h"

static uint32_t	rt_convert_color(t_rgb rgb)
{
	const uint32_t	r = (uint32_t)(rgb.r * 255);
	const uint32_t	g = (uint32_t)(rgb.g * 255);
	const uint32_t	b = (uint32_t)(rgb.b * 255);

	return ((r << 24) | (g << 16) | (b << 8) | 0xFF);
}

static t_ray	rt_create_ray(uint32_t x, uint32_t y, t_data *data)
{
	t_vector	pixel_ray_x = rt_scale(data->camera_right, x * data->dist_per_pix);
	t_vector	pixel_ray_y = rt_scale(data->camera_up, y * -data->dist_per_pix);
	t_vector	pixel_ray = rt_add(rt_add(data->canvas_top_left, pixel_ray_x), pixel_ray_y);
	t_vector	dir = rt_normalized(pixel_ray);

	return (rt_get_ray(data->camera->origin, dir));
}

void	rt_shoot_rays(t_data *data)
{
	size_t		ray_index;
	t_ray		ray;
	t_rgb		rgb;
	uint32_t	color;

	ray_index = 0;
	while (ray_index < RAYS_PER_FRAME && data->pixel_index > data->available_count)
	{
		data->pixel_index--;
		uint32_t location = data->available[data->pixel_index];
		uint32_t x = location % UNSCALED_WINDOW_WIDTH;
		uint32_t y = location / UNSCALED_WINDOW_WIDTH;

		ray = rt_create_ray(x, y, data);
		rgb = rt_get_ray_rgb(ray, data);
		color = rt_convert_color(rgb);

		// TODO: && data->update_radius >= SMALLEST_UPDATE_RADIUS_TO_USE_VORONOI
		if (data->draw_mode)
		{
			rt_voronoi_floodfill((int32_t)x, (int32_t)y, color, data);
		}
		else
		{
			uint32_t	dx;
			uint32_t	dy;

			dy = 0;
			while (dy < PIXEL_SCALE)
			{
				dx = 0;
				while (dx < PIXEL_SCALE)
				{
					mlx_put_pixel(data->image, x * PIXEL_SCALE + dx, y * PIXEL_SCALE + dy, color);
					dx++;
				}
				dy++;
			}
		}

		ray_index++;
	}
}
