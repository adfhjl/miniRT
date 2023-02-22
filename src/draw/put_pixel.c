/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   put_pixel.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/20 16:24:38 by sbos          #+#    #+#                 */
/*   Updated: 2023/02/22 16:01:21 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

uint32_t	rt_convert_color(t_rgb rgb)
{
	const uint32_t	r = (uint32_t)(rgb.r * 255);
	const uint32_t	g = (uint32_t)(rgb.g * 255);
	const uint32_t	b = (uint32_t)(rgb.b * 255);

	return ((r << 24) | (g << 16) | (b << 8) | 0xFF);
}

// TODO: Get rid of this in favor of rt_put_pixel_fast()
void	rt_put_pixel(mlx_image_t *image, uint32_t x, uint32_t y, t_rgb rgb)
{
	uint32_t	color;
	uint32_t	dx;
	uint32_t	dy;

	color = rt_convert_color(rgb);
	dy = 0;
	while (dy < PIXEL_SCALE)
	{
		dx = 0;
		while (dx < PIXEL_SCALE)
		{
			mlx_put_pixel(image, x * PIXEL_SCALE + dx, y * PIXEL_SCALE + dy, color);
			dx++;
		}
		dy++;
	}
}

// TODO: Probably only significantly faster when rt_convert_color() is only
// being called per drawn square with voronoi.
void	rt_put_pixel_fast(mlx_image_t *image, uint32_t x, uint32_t y, uint32_t color)
{
	uint32_t	*start;

	start = (uint32_t *)&image->pixels[(x + y * image->width) * sizeof(uint32_t)];
	*start = color;
}
