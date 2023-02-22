/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   put_pixel.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/20 16:24:38 by sbos          #+#    #+#                 */
/*   Updated: 2023/02/20 16:24:38 by sbos          ########   odam.nl         */
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
	mlx_put_pixel(image, x, y, rt_convert_color(rgb));
}

void	rt_put_pixel_fast(mlx_image_t *image, uint32_t x, uint32_t y, uint32_t color)
{
	uint32_t	*start;

	start = (uint32_t *)&image->pixels[(x + y * image->width) * sizeof(uint32_t)];
	*start = color;
}
