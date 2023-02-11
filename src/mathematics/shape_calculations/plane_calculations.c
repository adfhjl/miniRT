/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane_calculations.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbenneko <vbenneko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/03 17:08:36 by vbenneko      #+#    #+#                 */
/*   Updated: 2023/02/11 16:30:54 by vbenneko      ########   odam.nl         */
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
	if (denom == 0)
		return ((t_hit_info){.distance = INFINITY});
	info.distance = rt_dot(rt_sub(plane.origin, ray.origin), plane.normal) / denom;
	info.object = object;
	info.surface_normal = plane.normal;
	info.visual_surface_normal = 1;
	if ((rt_dot(info.surface_normal, ray.normal) > 0) != \
		(rt_dot(info.surface_normal, \
			// TODO: Don't need to call rt_normalized() since we're only doing < 0
				rt_normalized(rt_sub(data->light->origin, \
				rt_get_ray_point(ray, info.distance)))) < 0))
		info.visual_surface_normal = -1;
	return (info);
}

static t_rgb	rt_clamp_rgb(t_rgb rgb)
{
	return ((t_rgb){
		.r = fminf(rgb.r, 1.0),
		.g = fminf(rgb.g, 1.0),
		.b = fminf(rgb.b, 1.0)
	});
}

static t_rgb	rt_get_rgb_factor(t_hit_info info, t_hit_info light_ray_info,
		t_vector biased_point_to_light, t_data *data)
{
	const t_rgb			scaled_ambient = rt_scale_rgb(data->ambient->rgb,
			data->ambient->ratio);

	if (info.visual_surface_normal == -1 \
	|| light_ray_info.distance < rt_mag(biased_point_to_light))
	// || light_ray_info.distance - (float)EPSILON * 100 < rt_mag(biased_point_to_light))
		return (scaled_ambient);
	else
	// TODO: Replace `1.0f` with some distance factor
		return (rt_add_rgb(scaled_ambient, rt_scale_rgb(data->light->rgb,
					data->light->brightness * 1.0f)));
}

// C & N
// ^ & ^ = V // if (dot(c.normal, p.normal) > 0) return scale(p.normal, -1)
// V & ^ = ^ // return (p.normal)
// ^ & V = V // return (p.normal)
// V & V = ^ // if (dot(c.normal, p.normal) > 0) return scale(p.normal, -1)
static t_vector	rt_get_bias_unit_vector(t_vector camera_normal, t_vector object_normal)
{
	if (rt_dot(camera_normal, object_normal) > 0)
		return (rt_scale(object_normal, -1));
	return (object_normal);
}

t_rgb	rt_get_plane_point_rgb(t_ray ray, t_hit_info info, t_data *data)
{
	const t_vector		biased_point = rt_get_ray_point(rt_get_ray(
			rt_get_ray_point(ray, info.distance),
			rt_get_bias_unit_vector(ray.normal, info.object->plane.normal)),
			(float)EPSILON * 100);
	const t_hit_info	light_ray_info = rt_get_hit_info(rt_get_ray(
			biased_point, rt_sub(data->light->origin, biased_point)), data);
	const t_vector		biased_point_to_light = rt_sub(data->light->origin,
			biased_point);

	return (rt_clamp_rgb(rt_multiply_rgb(info.object->plane.rgb,
		rt_get_rgb_factor(info, light_ray_info, biased_point_to_light, data))));
}

// rgb=$pl_RGB * ($A_RGB * $A_LVL + $l_RGB * $l_LVL * $l_DST)
// rgb=$pl_RGB * ($A_RGB * $A_LVL) + $pl_RGB * ($l_RGB * $l_LVL * $l_DST)
