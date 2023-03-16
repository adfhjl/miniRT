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

#include "rt_structs.h"

#include "collisions/rt_collisions.h"
#include "rays/rt_rays.h"
#include "rgb/rt_rgb.h"
#include "utils/rt_utils.h"
#include "vectors/rt_vectors.h"

#include <math.h>

static float	rt_get_distance(t_quadratic q)
{
	if (q.solution_minus < 0)
		return (q.solution_plus);
	return (q.solution_minus);
}

static void	rt_update_info(t_ray ray, t_object sphere, t_hit_info *info,
				t_quadratic q)
{
	t_vector	collision;
	t_vector	sphere_to_collision;

	info->distance = rt_get_distance(q);
	collision = rt_get_ray_endpoint(ray, info->distance);
	sphere_to_collision = rt_sub(collision, sphere.pos);
	info->surface_normal = rt_normalized(sphere_to_collision);
	info->inside = false;
	if (q.solution_minus < 0)
	{
		info->surface_normal = rt_scale(info->surface_normal, -1);
		info->inside = true;
	}
	info->material = sphere.material;
	info->material.rgb = rt_get_line_rgb(ray, *info, sphere);
}

// Explanation:
// Source:	https://www.scratchapixel.com/lessons/3d-basic-rendering/
// 			minimal-ray-tracer-rendering-simple-shapes/
// 			ray-sphere-intersection.html#:~:text=Analytic%20Solution
// The equation for a sphere is x^2 + y^2 + z^2 = R^2.
// If x, y, z are coordinates of P, then it's P^2 - R^2 = 0.
// The equation for a ray where O is origin, D is direction, and
// t is distance, is O + Dt.
// Substitute to get (O + Dt)^2 - R^2 = 0 ->
// O^2 + (Dt)^2 + 2ODt - R^2 = 0 ->
// D^2t^2 + 2ODt + O^2 - R^2 = 0.
// This is a quadratic equation: at^2 + bt + c = 0
// So a = D^2, b = 2OD, and c = O^2 - R^2.
// O is sphere_to_ray_pos, to make the ray origin relative to the sphere center.
void	rt_get_sphere_collision_info(t_ray ray, t_object sphere,
			t_hit_info *info)
{
	t_vector	sphere_to_ray_pos;
	t_quadratic	q;
	float		distance;

	sphere_to_ray_pos = rt_sub(ray.pos, sphere.pos);
	q = rt_solve_quadratic(rt_mag2(ray.dir),
			2 * rt_dot(ray.dir, sphere_to_ray_pos),
			rt_mag2(sphere_to_ray_pos) - sphere.diameter * sphere.diameter / 4);
	if (!q.solution)
		return ;
	distance = rt_get_distance(q);
	if (distance > 0 && distance < info->distance)
		rt_update_info(ray, sphere, info, q);
}
