/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_mathematics_utils.h                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/17 14:53:02 by sbos          #+#    #+#                 */
/*   Updated: 2023/02/17 14:53:02 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_MATHEMATICS_UTILS_H
# define RT_MATHEMATICS_UTILS_H

# include "minirt.h"

t_vector	rt_add(t_vector a, t_vector b);
t_rgb		rt_add_rgb(t_rgb a, t_rgb b);

t_vector	rt_cross(t_vector a, t_vector b);

float		rt_dot(t_vector a, t_vector b);

t_vector	rt_get_ray_point(t_ray ray, float t);

float		rt_mag(t_vector v);

t_rgb		rt_multiply_rgb(t_rgb a, t_rgb b);

t_vector	rt_normalized(t_vector v);

t_vector	rt_scale(t_vector v, float f);
t_rgb		rt_scale_rgb(t_rgb v, float f);

t_vector	rt_sub(t_vector a, t_vector b);

#endif
