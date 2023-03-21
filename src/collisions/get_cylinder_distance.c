/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_cylinder_distance.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 16:30:42 by sbos          #+#    #+#                 */
/*   Updated: 2023/03/17 16:30:42 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rt_structs.h"

#include "utils/rt_utils.h"
#include "vectors/rt_vectors.h"

#include <math.h>

static float	rt_get_sq_radius(float diameter)
{
	return (diameter / 2 * diameter / 2);
}

// Note: this is not normalized, but this is intended.
static t_ray	rt_get_flattened_ray(t_ray ray)
{
	ray.pos.y = 0;
	ray.dir.y = 0;
	return (ray);
}

/*
1. Dot product between cylinder.normal and {0, 1, 0}
   gives the sin() of the angle between the two
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
		ray.dir = rt_rotate_around_axis(ray.dir, rotation_axis, theta);
	}
	return (ray);
}

float	rt_get_cylinder_distance(t_ray ray, t_object cylinder, bool *inside)
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
			rt_mag2(flattened_ray.pos) - rt_get_sq_radius(cylinder.diameter));
	if (!q.solution)
		return (INFINITY);
	if (q.solution_minus > 0)
	{
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
