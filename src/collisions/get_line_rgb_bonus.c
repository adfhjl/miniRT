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

#include "rt_structs.h"

#include "vectors/rt_vectors.h"

#include <math.h>

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

static bool	rt_is_striped(float n, float frequency)
{
	return ((bool)rt_abs(fmodf(floorf(n * frequency), 2)));
}

// fmodf is the remainder operation; so fmodf(-3.5f, 1.0f) is -0.5f
// floorf rounds towards -infinity: floorf(-3.1) is -4.0f
t_rgb	rt_get_line_rgb(t_ray ray, t_hit_info info, t_object object)
{
	t_vector	pos;
	bool		x;
	bool		y;
	bool		z;

	pos = rt_add(ray.pos, rt_scale(ray.dir, info.distance));
	pos = rt_add(pos, object.material.line_offset);
	x = rt_is_striped(pos.x, object.material.line_frequency.x);
	y = rt_is_striped(pos.y, object.material.line_frequency.y);
	z = rt_is_striped(pos.z, object.material.line_frequency.z);
	if (rt_xor3(x, y, z))
		return (rt_sub((t_vector){1, 1, 1}, info.material.rgb));
	return (info.material.rgb);
}
