/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_rgb.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/01 19:17:04 by sbos          #+#    #+#                 */
/*   Updated: 2023/03/01 19:17:04 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_RGB_H
# define RT_RGB_H

#include "rt_structs.h"

t_rgb	rt_aces_film(t_rgb x);

t_rgb	rt_add_scalar_rgb(t_rgb a, float b);

t_rgb	rt_clamp_rgb(t_rgb a, float lower, float upper);

t_rgb	rt_linear_to_srgb(t_rgb rgb);
t_rgb	rt_srgb_to_linear(t_rgb rgb);

t_rgb	rt_divide_rgb(t_rgb a, t_rgb b);

t_rgb	rt_exp_rgb(t_rgb rgb);

t_rgb	rt_multiply_rgb(t_rgb a, t_rgb b);

#endif
