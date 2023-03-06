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

#include "get_structs/rt_get_structs.h"
#include "vectors/rt_vectors.h"
#include "rays/rt_rays.h"
#include "rgb/rt_rgb.h"

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
	t_hit_info	info;
	float		denom;

	denom = rt_dot(ray.dir, plane.normal);
	if (denom == 0)
		return ((t_hit_info){.distance = INFINITY});
	info.distance = rt_dot(rt_sub(plane.pos, ray.pos), plane.normal) / denom;
	info.surface_normal = plane.normal;
	if (rt_dot(ray.dir, info.surface_normal) > 0)
		info.surface_normal = rt_scale(info.surface_normal, -1);
	info.rgb = plane.rgb;
	info.emissive = rt_scale(info.rgb, PLANE_EMISSIVE_FACTOR);
	info.specularity = PLANE_SPECULAR_FACTOR;
	info.roughness = PLANE_ROUGHNESS_FACTOR;
	info.specular_color = (t_rgb){PLANE_SPECULAR_R, PLANE_SPECULAR_G, PLANE_SPECULAR_B};
	return (info);
}
