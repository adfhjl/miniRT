/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbenneko <vbenneko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/03 17:11:26 by vbenneko      #+#    #+#                 */
/*   Updated: 2023/02/22 17:19:14 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#include "get_structs/rt_get_structs.h"
#include "mathematics/rt_mathematics.h"
#include "rays/rt_rays.h"

// TODO: Maybe write this
// static float	rt_quadratic_formula(*solution_1, *solution_2)
// {
// 	// *solution_1 = INFINITY;
// 	// *solution_2 = INFINITY;
// 	return (distance);
// }

static float	get_sphere_distance(t_object sphere, t_ray ray)
{
	const float	a = rt_dot(ray.normal, ray.normal);
	const float	b = 2 * rt_dot(ray.normal, rt_sub(ray.origin, sphere.origin));
	const float	c = rt_dot(rt_sub(ray.origin, sphere.origin), rt_sub(ray.origin,
				sphere.origin)) - sphere.diameter * sphere.diameter / 4;
	const float	d = (b * b) - (4 * a * c);
	float		distance;

	if (d < 0)
		return (INFINITY);
	distance = (-b - sqrtf(d)) / (2 * a);
	if (distance <= 0)
	{
		distance = (-b + sqrtf(d)) / (2 * a);
		if (distance <= 0)
			return (INFINITY);
	}
	return (distance);
}

t_hit_info	rt_get_sphere_collision_info(t_ray ray, t_object sphere)
{
	t_hit_info	info;

	info.distance = get_sphere_distance(sphere, ray);
	if (info.distance == INFINITY)
		return ((t_hit_info){.distance = INFINITY});
	info.surface_normal = rt_normalized(rt_sub(rt_get_ray_point(ray,
					info.distance), sphere.origin));
	info.rgb = sphere.rgb;
	info.emissive = rt_get_rgb(0, 0, 0);
	info.flip_factor = 1;
	return (info);
}
