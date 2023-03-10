/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_line_rgb_bonus.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/10 15:22:51 by sbos          #+#    #+#                 */
/*   Updated: 2023/03/10 15:22:51 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#include "vectors/rt_vectors.h"

// x == y == z is an XOR:
// x y z r
// 0 0 0 0
// 1 0 0 1
// 0 1 0 1
// 0 0 1 1
// 1 1 0 0
// 1 0 1 0
// 0 1 1 0
// 1 1 1 1
static bool	rt_xor3(bool x, bool y, bool z)
{
	return (x ^ y ^ z);
}

static float	rt_abs(float n)
{
	if (n < 0)
		return (-n);
	return (n);
}

// fmodf is the remainder operation; so fmodf(-3.5f, 1.0f) is -0.5f
// floorf rounds towards -infinity: floorf(-3.1) is -4.0f
t_rgb	rt_get_line_rgb(t_ray ray, t_hit_info info, t_object object)
{
	t_vector	pos;
	float		x;
	float		y;
	float		z;

	pos = rt_add(ray.pos, rt_scale(ray.dir, info.distance));
	x = rt_abs(fmodf(floorf(pos.x * object.x_line_frequency), 2));
	y = rt_abs(fmodf(floorf(pos.y * object.y_line_frequency), 2));
	z = rt_abs(fmodf(floorf(pos.z * object.z_line_frequency), 2));
	if (rt_xor3((bool)x, (bool)y, (bool)z))
		return (info.material.rgb);
	return (rt_sub((t_vector){1, 1, 1}, info.material.rgb));
}
