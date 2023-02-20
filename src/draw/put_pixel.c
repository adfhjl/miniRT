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

static uint32_t	rt_convert_color(t_rgb rgb)
{
	const uint32_t	r = (uint32_t)(rgb.r * 255);
	const uint32_t	g = (uint32_t)(rgb.g * 255);
	const uint32_t	b = (uint32_t)(rgb.b * 255);

	return ((r << 24) | (g << 16) | (b << 8) | 0xFF);
}

void	rt_put_pixel(mlx_image_t *image, uint32_t x, uint32_t y, t_rgb rgb)
{
	mlx_put_pixel(image, x, y, rt_convert_color(rgb));
}
