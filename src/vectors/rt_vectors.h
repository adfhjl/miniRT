/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_vectors.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/17 14:53:02 by sbos          #+#    #+#                 */
/*   Updated: 2023/02/17 14:53:02 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_VECTORS_H
# define RT_VECTORS_H

# include "minirt.h"

t_vector	rt_add(t_vector a, t_vector b);

t_vector	rt_cross(t_vector a, t_vector b);

float		rt_dot(t_vector a, t_vector b);

float		rt_mag2(t_vector v);
float		rt_mag(t_vector v);

t_vector	rt_normalized(t_vector v);

t_vector	rt_reflect(t_vector d, t_vector n);

t_vector	rt_rotate_around_axis(t_vector v, t_vector rotation_axis,
				float theta);

t_vector	rt_scale(t_vector v, float f);

t_vector	rt_sub(t_vector a, t_vector b);

#endif
