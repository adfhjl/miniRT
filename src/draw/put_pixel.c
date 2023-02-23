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

	return (0xFF000000 | (b << 16) | (g << 8) | r);
}

void	rt_put_color(mlx_image_t *image, uint32_t x, uint32_t y, uint32_t color)
{
	uint32_t	dx;
	uint32_t	dy;
	size_t		scaled_x;
	size_t		scaled_y;
	size_t		index;

	dy = 0;
	while (dy < PIXEL_SCALE)
	{
		dx = 0;
		while (dx < PIXEL_SCALE)
		{
			scaled_x = x * PIXEL_SCALE + dx;
			scaled_y = y * PIXEL_SCALE + dy;
			index = (scaled_x + scaled_y * image->width) * sizeof(uint32_t);
			*(uint32_t *)&image->pixels[index] = color;
			dx++;
		}
		dy++;
	}
}

void	rt_put_rgb(mlx_image_t *image, uint32_t x, uint32_t y, t_rgb rgb)
{
	rt_put_color(image, x, y, rt_convert_color(rgb));
}
