/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane_calculations.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbenneko <vbenneko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/03 17:08:36 by vbenneko      #+#    #+#                 */
/*   Updated: 2023/02/14 14:43:21 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Equation 1:
// ray.origin + ray.normal * t = rayEnd
//
// Equation 2:
// dot(rayEnd - plane.origin, plane.normal) = 0
//
// Substitute rayEnd from equation 1 in equation 2:
// dot(ray.origin + ray.normal * t - plane.origin, plane.normal) = 0
//
// Solve for t:
// Fact: The dot product is distributive; that is, dot(v1 + v2, v3) = dot(v1, v3) + dot(v2, v3)
// dot(ray.normal * t, plane.normal) + dot(ray.origin - plane.origin, plane.normal) = 0
//
// dot(ray.normal * t, plane.normal) = -dot(ray.origin - plane.origin, plane.normal)
//
// Fact: The dot product abides to scalar multiplication; that is, dot(s1 * v1, v2) = s1 * dot(v1, v2)
// t * dot(ray.normal, plane.normal) = -dot(ray.origin - plane.origin, plane.normal)
//
// t = -dot(ray.origin - plane.origin, plane.normal) / dot(ray.normal, plane.normal)
//
// t = dot(plane.origin - ray.origin, plane.normal) / dot(ray.normal, plane.normal)
//
// denom = dot(ray.normal, plane.normal):
// t = dot(plane.origin - ray.origin, plane.normal) / denom
t_hit_info	rt_get_plane_collision_info(
	t_ray ray, t_object *object, t_data *data)
{
	t_hit_info		info;
	const t_plane	plane = object->plane;
	float			denom;

	denom = rt_dot(ray.normal, plane.normal);
	// TODO: Is this if-statement necessary? float / 0 is infinity anyways?
	if (denom == 0)
		return ((t_hit_info){.distance = INFINITY});
	info.distance = rt_dot(rt_sub(plane.origin, ray.origin), plane.normal) / denom;
	info.object = object;
	info.surface_normal = plane.normal;
	info.visibility = rt_get_visibility(info, ray, data->light);
	return (info);
}
