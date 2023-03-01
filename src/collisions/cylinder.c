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
#include "utils/rt_utils.h"
#include "vectors/rt_vectors.h"

/*
1. Dot product between cylinder.normal and {0, 1, 0} gives the sin() of the angle between the two
2. theta = asinf(angle)
3. rotation_axis = rt_cross(cylinder.normal, {0, 1, 0})
4. ray.pos = rt_rotate_around_axis(ray.pos, rotation_axis, theta)
5. ray.dir = rt_rotate_around_axis(ray.dir, rotation_axis, theta)
*/
static t_ray	rt_get_perspective_ray(t_ray ray, t_object cylinder)
{
	// TODO: Maybe don't use shitty {0, 1, 0}
	float		angle;
	float		theta;
	t_vector	rotation_axis;

	ray = rt_get_ray(rt_sub(ray.pos, cylinder.pos), ray.dir);
	if (cylinder.normal.x != 0.0f || cylinder.normal.z != 0.0f)
	{
		angle = rt_dot(cylinder.normal, (t_vector){0, 1, 0});
		theta = acosf(angle);
		rotation_axis = rt_normalized(rt_cross(cylinder.normal, (t_vector){0, 1, 0}));
		ray.pos = rt_rotate_around_axis(ray.pos, rotation_axis, theta);
		ray.dir = rt_rotate_around_axis(ray.dir, rotation_axis, theta);
		rt_assert_normal(ray.dir);
	}
	return (ray);
}

// Note: not normalized, this is intended
static t_ray	rt_get_flattened_ray(t_ray ray)
{
	ray.pos.y = 0;
	ray.dir.y = 0;
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
		v = rt_get_ray_point(perspective_ray, q.solution_minus);
		if (v.y <= cylinder.height / 2 && v.y >= -cylinder.height / 2)
			return (q.solution_minus);
	}
	*inside = true;
	v = rt_get_ray_point(perspective_ray, q.solution_plus);
	if (v.y <= cylinder.height / 2 && v.y >= -cylinder.height / 2)
		return (q.solution_plus);
	return (INFINITY);
}

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

t_hit_info	rt_get_cylinder_collision_info(t_ray ray, t_object cylinder)
{
	t_hit_info	info;
	bool		inside;

	info.distance = rt_get_cylinder_distance(ray, cylinder, &inside);
	if (info.distance == INFINITY)
		return ((t_hit_info){.distance = INFINITY});
	info.surface_normal = rt_get_cylinder_surface_normal(rt_get_ray_point(ray, info.distance), cylinder);
	if (inside)
		info.surface_normal = rt_scale(info.surface_normal, -1);
	info.rgb = cylinder.rgb;
	info.emissive = rt_get_rgb(0, 0, 0);
	return (info);
}
