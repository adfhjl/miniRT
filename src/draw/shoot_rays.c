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

static t_ray	rt_create_ray(uint32_t x, uint32_t y, t_data *data)
{
	t_vector	pixel_ray_x = rt_scale(data->camera_right, x * data->dist_per_pix);
	t_vector	pixel_ray_y = rt_scale(data->camera_up, y * -data->dist_per_pix);
	t_vector	pixel_ray = rt_add(rt_add(data->canvas_top_left, pixel_ray_x), pixel_ray_y);
	t_vector	dir = rt_normalized(pixel_ray);

	return (rt_get_ray(data->camera->origin, dir));
}

static t_rgb	rt_shoot_ray(uint32_t x, uint32_t y, t_data *data)
{
	t_ray		ray;

	ray = rt_create_ray(x, y, data);
	return (rt_get_ray_rgb(ray, data));
}

static void	rt_shoot_voronoi_ray(t_data *data)
{
	uint32_t 	location;
	uint32_t	x;
	uint32_t	y;
	t_rgb		rgb;

	data->pixel_index--;
	location = data->available[data->pixel_index];
	x = location % UNSCALED_WINDOW_WIDTH;
	y = location / UNSCALED_WINDOW_WIDTH;
	rgb = rt_shoot_ray(x, y, data);
	rt_voronoi_floodfill((int32_t)x, (int32_t)y, rgb, data);
}

static void	rt_shoot_blue_noise_ray(t_data *data)
{
	uint32_t	location;
	uint32_t	x;
	uint32_t	y;
	t_rgb		rgb;

	data->pixel_index--;
	location = data->available[data->pixel_index];
	x = location % UNSCALED_WINDOW_WIDTH;
	y = location / UNSCALED_WINDOW_WIDTH;
	rgb = rt_shoot_ray(x, y, data);
	rt_put_pixel(data->image, x, y, rgb);
}

static void	rt_shoot_normal_ray(t_data *data)
{
	uint32_t	location;
	uint32_t	x;
	uint32_t	y;
	t_rgb		rgb;

	data->pixel_index--;
	location = data->pixel_count - data->pixel_index;
	x = location % UNSCALED_WINDOW_WIDTH;
	y = location / UNSCALED_WINDOW_WIDTH;
	rgb = rt_shoot_ray(x, y, data);
	rt_put_pixel(data->image, x, y, rgb);
}

void	rt_shoot_rays(t_data *data)
{
	size_t		ray_index;

	ray_index = 0;
	while (ray_index < RAYS_PER_FRAME)
	{
		// TODO: && data->update_radius >= SMALLEST_UPDATE_RADIUS_TO_USE_VORONOI
		if (data->draw_mode == DRAW_MODE_VORONOI)
		{
			if (data->pixel_index <= data->available_count)
				return ;
			rt_shoot_voronoi_ray(data);
		}
		else if (data->draw_mode == DRAW_MODE_BLUE_NOISE)
		{
			if (data->pixel_index <= data->available_count)
				return ;
			rt_shoot_blue_noise_ray(data);
		}
		else if (data->draw_mode == DRAW_MODE_NORMAL)
		{
			if (data->pixel_index == 0)
				return ;
			rt_shoot_normal_ray(data);
		}
		ray_index++;
	}
}
