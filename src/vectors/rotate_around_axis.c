/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rotate_around_axis.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/01 19:19:30 by sbos          #+#    #+#                 */
/*   Updated: 2023/03/01 19:19:30 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#include "vectors/rt_vectors.h"

// https://en.wikipedia.org/wiki/Rodrigues%27_rotation_formula#Statement
t_vector	rt_rotate_around_axis(t_vector v, t_vector rotation_axis,
				float theta)
{
	return (rt_add(rt_add(rt_scale(v, cosf(theta)),
	rt_scale(rt_cross(rotation_axis, v), sinf(theta))),
	rt_scale(rotation_axis, rt_dot(rotation_axis, v) * (1 - cosf(theta)))));
}