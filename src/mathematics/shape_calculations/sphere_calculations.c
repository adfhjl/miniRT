/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere_calculations.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbenneko <vbenneko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/03 17:11:26 by vbenneko      #+#    #+#                 */
/*   Updated: 2023/02/14 14:43:34 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static float	get_sphere_distance(t_sphere sphere, t_ray ray)
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

t_hit_info	rt_get_sphere_collision_info(
	t_ray ray, t_object *object, t_data *data)
{
	const t_sphere	sphere = object->sphere;
	t_hit_info		info;

	info.distance = get_sphere_distance(sphere, ray);
	if (info.distance == INFINITY)
		return ((t_hit_info){.distance = INFINITY});
	info.object = object;
	info.surface_normal = rt_normalized(rt_sub(rt_get_ray_point(ray,
					info.distance), sphere.origin));
	info.visibility = rt_get_visibility(info, ray, data->light);
	return (info);
}
