/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbenneko <vbenneko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/03 17:08:36 by vbenneko      #+#    #+#                 */
/*   Updated: 2023/02/22 17:19:09 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#include "vectors/rt_vectors.h"
#include "rays/rt_rays.h"
#include "rgb/rt_rgb.h"

static float	rt_abs(float n)
{
	if (n < 0)
		return (-n);
	return (n);
}

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
static bool		rt_xor3(bool x, bool y, bool z)
{
	return (x ^ y ^ z);
}

// fmodf is the remainder operation; so fmodf(-3.5f, 1.0f) is -0.5f
// floorf rounds towards -infinity: floorf(-3.1) is -4.0f
static t_rgb	rt_get_checkerboard_rgb(t_ray ray, t_hit_info info)
{
	t_vector	pos;
	float		x;
	float		y;
	float		z;

	pos = rt_add(ray.pos, rt_scale(ray.dir, info.distance));
	x = rt_abs(fmodf(floorf(pos.x * X_LINE_FREQUENCY), 2));
	y = rt_abs(fmodf(floorf(pos.y * Y_LINE_FREQUENCY), 2));
	z = rt_abs(fmodf(floorf(pos.z * Z_LINE_FREQUENCY), 2));
	if (rt_xor3((bool)x, (bool)y, (bool)z))
		return ((t_vector){0, 0, 0});
	return ((t_vector){1, 1, 1});
}

// Equation 1:
// ray.pos + ray.dir * t = rayEnd
//
// Equation 2:
// dot(rayEnd - plane.pos, plane.normal) = 0
//
// Substitute rayEnd from equation 1 in equation 2:
// dot(ray.pos + ray.dir * t - plane.pos, plane.normal) = 0
//
// Solve for t:
// Fact: The dot product is distributive; that is, dot(v1 + v2, v3) = dot(v1, v3) + dot(v2, v3)
// dot(ray.dir * t, plane.normal) + dot(ray.pos - plane.pos, plane.normal) = 0
//
// dot(ray.dir * t, plane.normal) = -dot(ray.pos - plane.pos, plane.normal)
//
// Fact: The dot product abides to scalar multiplication; that is, dot(s1 * v1, v2) = s1 * dot(v1, v2)
// t * dot(ray.dir, plane.normal) = -dot(ray.pos - plane.pos, plane.normal)
//
// t = -dot(ray.pos - plane.pos, plane.normal) / dot(ray.dir, plane.normal)
//
// t = dot(plane.pos - ray.pos, plane.normal) / dot(ray.dir, plane.normal)
//
// denom = dot(ray.dir, plane.normal):
// t = dot(plane.pos - ray.pos, plane.normal) / denom
t_hit_info	rt_get_plane_collision_info(t_ray ray, t_object plane)
{
	float		denom;
	t_hit_info	info;

	denom = rt_dot(ray.dir, plane.normal);
	if (denom == 0)
		return ((t_hit_info){.distance = INFINITY});
	info.distance = rt_dot(rt_sub(plane.pos, ray.pos), plane.normal) / denom;
	info.surface_normal = plane.normal;
	if (rt_dot(ray.dir, info.surface_normal) > 0)
		info.surface_normal = rt_scale(info.surface_normal, -1);
	info.rgb = plane.rgb;
	if (DRAW_LINES)
		info.rgb = rt_get_checkerboard_rgb(ray, info);
	info.emissive = rt_scale(plane.rgb, PLANE_EMISSIVE_FACTOR);
	info.specular_chance = PLANE_SPECULAR_CHANCE;
	info.specular_roughness = PLANE_SPECULAR_ROUGHNESS;
	info.index_of_refraction = PLANE_INDEX_OF_REFRACTION;
	info.refraction_chance = PLANE_REFRACTION_CHANCE;
	info.refraction_roughness = PLANE_REFRACTION_ROUGHNESS;
	return (info);
}
