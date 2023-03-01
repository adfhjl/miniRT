/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbenneko <vbenneko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/03 17:12:17 by vbenneko      #+#    #+#                 */
/*   Updated: 2023/02/23 17:37:43 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#include "debug/rt_debug.h"
#include "get_structs/rt_get_structs.h"
#include "rays/rt_rays.h"

static t_ray	rt_translate_ray(t_ray ray, t_object cylinder)
{
	return (rt_get_ray(rt_sub(ray.pos, cylinder.pos), ray.dir));
}

// https://en.wikipedia.org/wiki/Rodrigues%27_rotation_formula#Statement
static t_vector	rt_rotate_around_axis(t_vector v, t_vector rotation_axis,
				float theta)
{
	return (rt_add(rt_add(rt_scale(v, cosf(theta)),
	rt_scale(rt_cross(rotation_axis, v), sinf(theta))),
	rt_scale(rotation_axis, rt_dot(rotation_axis, v) * (1 - cosf(theta)))));
}

/*
1. Dot product between cylinder.normal and {0, 1, 0} gives the sin() of the angle between the two
2. theta = asinf(angle)
3. rotation_axis = rt_cross(cylinder.normal, {0, 1, 0})
4. ray.pos = rt_rotate_around_axis(ray.pos, rotation_axis, theta)
5. ray.dir = rt_rotate_around_axis(ray.dir, rotation_axis, theta)
*/
static t_ray	rt_rotate_ray(t_ray ray, t_object cylinder000)
{
	// TODO: Maybe don't use shitty {0, 1, 0}
	float		angle;
	float		theta;
	t_vector	rotation_axis;

	angle = rt_dot(cylinder000.normal, (t_vector){0, 1, 0});
	theta = acosf(angle);
	rotation_axis = rt_normalized(rt_cross(cylinder000.normal, (t_vector){0, 1, 0}));
	ray.pos = rt_rotate_around_axis(ray.pos, rotation_axis, theta);
	ray.dir = rt_rotate_around_axis(ray.dir, rotation_axis, theta);
	rt_assert_normal(ray.dir);
	return (ray);
}

static t_ray	rt_adjust_ray(t_ray ray, t_object cylinder)
{
	ray = rt_translate_ray(ray, cylinder);
	if (cylinder.normal.x != 0.0f || cylinder.normal.z != 0.0f)
		ray = rt_rotate_ray(ray, cylinder);
	return (ray);
}

// static float	rt_get_cylinder_distance(t_ray ray, t_object cylinder)
// {
// 	const t_ray	adjusted_ray = rt_adjust_ray(ray, cylinder);
// 	const float	a = rt_mag2(adjusted_ray.dir);
// 	const float	b = 2 * rt_dot(adjusted_ray.dir, adjusted_ray.pos);
// 	const float	c = rt_mag2(adjusted_ray.pos)
// 		- cylinder.diameter * cylinder.diameter / 4;
// 	const float	d = (b * b) - (4 * a * c);
// 	float		distance;

// 	if (d < 0)
// 		return (INFINITY);
// 	distance = (-b - sqrtf(d)) / (2 * a);
// }

static float	rt_get_cylinder_distance(t_ray ray, t_object cylinder)
{
	const t_ray	adjusted_ray = rt_adjust_ray(ray, cylinder);
	t_ray	flattened_ray = adjusted_ray;
	flattened_ray.pos.y = 0;
	flattened_ray.dir.y = 0;
	float mag = rt_mag(flattened_ray.dir);
	flattened_ray.dir = rt_scale(flattened_ray.dir, 1 / mag);
	const float	a = rt_mag2(flattened_ray.dir);
	const float	b = 2 * rt_dot(flattened_ray.dir, flattened_ray.pos);
	const float	c = rt_mag2(flattened_ray.pos)
		- cylinder.diameter * cylinder.diameter / 4;
	const float	d = (b * b) - (4 * a * c);
	float		distance;

	if (d < 0)
		return (INFINITY);
	distance = (-b - sqrtf(d)) / (2 * a) / mag;
	if (distance > 0) {
		t_vector	v = rt_get_ray_point(adjusted_ray, distance);
		if (v.y <= cylinder.height / 2 && v.y >= -cylinder.height / 2)
			return (distance);
	}
	distance = (-b + sqrtf(d)) / (2 * a) / mag;
	if (distance > 0) {
		t_vector	v = rt_get_ray_point(adjusted_ray, distance);
		if (v.y <= cylinder.height / 2 && v.y >= -cylinder.height / 2)
			return (distance);
	}
	return (INFINITY);
}

static t_vector	rt_get_cylinder_surface_normal(t_vector ray_point,
				t_object cylinder)
{
	t_vector	point_direction;
	t_vector	perpendicular;
	t_vector	surface_abnormal;

	// TODO: Maybe normalize all of these?
	point_direction = rt_sub(ray_point, cylinder.pos);
	perpendicular = rt_cross(cylinder.normal, point_direction);
	surface_abnormal = rt_cross(perpendicular, cylinder.normal);
	return (rt_normalized(surface_abnormal));
}

t_hit_info	rt_get_cylinder_collision_info(t_ray ray, t_object cylinder)
{
	t_hit_info	info;

	info.distance = rt_get_cylinder_distance(ray, cylinder);
	if (info.distance == INFINITY)
		return ((t_hit_info){.distance = INFINITY});
	info.surface_normal = rt_get_cylinder_surface_normal(rt_get_ray_point(ray, info.distance), cylinder);
	info.rgb = cylinder.rgb;
	info.emissive = rt_get_rgb(0, 0, 0);
	return (info);
}
