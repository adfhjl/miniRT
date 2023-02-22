/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_draw.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/17 14:43:24 by sbos          #+#    #+#                 */
/*   Updated: 2023/02/17 14:43:24 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_DRAW_H
# define RT_DRAW_H

# include "minirt.h"

void	rt_generate_noise(t_data *data);

void	rt_draw_loop(void *param);

uint32_t	rt_convert_color(t_rgb rgb);
void	rt_put_pixel(mlx_image_t *image, uint32_t x, uint32_t y, t_rgb rgb); // TODO: Remove
void	rt_put_pixel_fast(mlx_image_t *image, uint32_t x, uint32_t y, uint32_t color);

void	rt_reset_canvas_info(t_data *data);

void	rt_shoot_rays(t_data *data);

void	rt_voronoi_floodfill(int32_t start_x, int32_t start_y, t_rgb rgb,
			t_data *data);

#endif
