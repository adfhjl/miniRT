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
	t_ray		ray;
	t_rgb		rgb;
	size_t	ray_index;

	ray_index = 0;
	while (ray_index < RAYS_PER_FRAME && data->pixel_index > data->available_count)
	{
		data->pixel_index--;
		uint32_t location = data->available[data->pixel_index];
		uint32_t x = location % WINDOW_WIDTH;
		uint32_t y = location / WINDOW_WIDTH;
		ray = rt_create_ray(x, y, data); // TODO: Revamp this function to not recalculate stuff unnecesarally
		rgb = rt_get_ray_rgb(ray, data);
		mlx_put_pixel(data->image, x, y, rt_convert_color(rgb));
		ray_index++;
	}
}
