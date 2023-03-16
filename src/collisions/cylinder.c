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

#include "rt_structs.h"

#include "collisions/rt_collisions.h"
#include "rgb/rt_rgb.h"
#include "tracing/rt_tracing.h"
#include "utils/rt_utils.h"
#include "vectors/rt_vectors.h"

#include <math.h>

#include "debug/rt_debug.h" // TODO: REMOVE

static t_vector	rt_get_cylinder_surface_normal(t_vector ray_point,
				t_object cylinder)
{
	t_vector	point_direction;
	t_vector	perpendicular;
	t_vector	surface_abnormal;

	point_direction = rt_sub(ray_point, cylinder.pos);
	perpendicular = rt_cross(cylinder.normal, point_direction);
	surface_abnormal = rt_cross(perpendicular, cylinder.normal);
	return (rt_normalized(surface_abnormal));
}

static void	rt_update_info(t_ray ray, t_object cylinder, t_hit_info *info,
				float distance)
{
	info->distance = distance;
	info->surface_normal = rt_get_cylinder_surface_normal(rt_get_ray_endpoint(ray, distance), cylinder);
	info->inside = false;
	info->material = cylinder.material;
	info->material.rgb = rt_get_line_rgb(ray, *info, cylinder);
}

// Note: not normalized, this is intended
static t_ray	rt_get_flattened_ray(t_ray ray)
{
	ray.pos.y = 0;
	ray.dir.y = 0;
	return (ray);
}

/*
1. Dot product between cylinder.normal and {0, 1, 0} gives the sin() of the angle between the two
2. theta = asinf(angle)
3. rotation_axis = rt_cross(cylinder.normal, {0, 1, 0})
4. ray.pos = rt_rotate_around_axis(ray.pos, rotation_axis, theta)
5. ray.dir = rt_rotate_around_axis(ray.dir, rotation_axis, theta)
*/
static t_ray	rt_get_perspective_ray(t_ray ray, t_object cylinder)
{
	t_vector	world_up;
	float		angle;
	float		theta;
	t_vector	rotation_axis;

	world_up = (t_vector){0, 1, 0};
	ray = rt_get_ray(rt_sub(ray.pos, cylinder.pos), ray.dir);
	if (cylinder.normal.x != 0.0f || cylinder.normal.z != 0.0f)
	{
		angle = rt_dot(cylinder.normal, world_up);
		theta = acosf(angle);
		rotation_axis = rt_normalized(rt_cross(cylinder.normal, world_up));
		ray.pos = rt_rotate_around_axis(ray.pos, rotation_axis, theta);
		rt_assert_normal(ray.dir, "a");
		ray.dir = rt_rotate_around_axis(ray.dir, rotation_axis, theta);
		rt_assert_normal(ray.dir, "b");
	}
	return (ray);
}

static float	rt_get_cylinder_distance(t_ray ray, t_object cylinder,
					bool *inside)
{
	t_ray		perspective_ray;
	t_ray		flattened_ray;
	t_quadratic	q;
	t_vector	v;

	*inside = false;
	perspective_ray = rt_get_perspective_ray(ray, cylinder);
	flattened_ray = rt_get_flattened_ray(perspective_ray);
	q = rt_solve_quadratic(rt_mag2(flattened_ray.dir),
			2 * rt_dot(flattened_ray.dir, flattened_ray.pos),
			rt_mag2(flattened_ray.pos) - cylinder.diameter * cylinder.diameter / 4);
	if (!q.solution)
		return (INFINITY);
	if (q.solution_minus > 0) {
		v = rt_get_ray_endpoint(perspective_ray, q.solution_minus);
		if (v.y <= cylinder.height / 2 && v.y >= -cylinder.height / 2)
			return (q.solution_minus);
	}
	*inside = true;
	v = rt_get_ray_endpoint(perspective_ray, q.solution_plus);
	if (v.y <= cylinder.height / 2 && v.y >= -cylinder.height / 2)
		return (q.solution_plus);
	return (INFINITY);
}

void	rt_get_cylinder_collision_info(t_ray ray, t_object cylinder,
			t_hit_info *info)
{
	float	distance;
	bool	inside;

	distance = rt_get_cylinder_distance(ray, cylinder, &inside);
	if (distance > 0 && distance < info->distance)
	{
		rt_update_info(ray, cylinder, info, distance);
		if (inside)
			info->surface_normal = rt_scale(info->surface_normal, -1);
	}
}
