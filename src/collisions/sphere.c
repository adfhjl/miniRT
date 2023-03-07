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

#include "rays/rt_rays.h"
#include "rgb/rt_rgb.h"
#include "utils/rt_utils.h"
#include "vectors/rt_vectors.h"

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
t_hit_info	rt_get_sphere_collision_info(t_ray ray, t_object sphere)
{
	t_vector	sphere_to_ray_pos;
	t_quadratic	q;
	t_hit_info	info;
	t_vector	collision;
	t_vector	sphere_to_collision;

	sphere_to_ray_pos = rt_sub(ray.pos, sphere.pos);
	q = rt_solve_quadratic(rt_mag2(ray.dir),
			2 * rt_dot(ray.dir, sphere_to_ray_pos),
			rt_mag2(sphere_to_ray_pos) - sphere.diameter * sphere.diameter / 4);
	if (!q.solution)
		return ((t_hit_info){.distance = INFINITY});
	info.distance = q.solution_minus;
	if (q.solution_minus < 0)
		info.distance = q.solution_plus;
	collision = rt_get_ray_point(ray, info.distance);
	sphere_to_collision = rt_sub(collision, sphere.pos);
	info.surface_normal = rt_normalized(sphere_to_collision);
	if (q.solution_minus < 0)
		info.surface_normal = rt_scale(info.surface_normal, -1);
	info.rgb = sphere.rgb;
	info.emissive = rt_scale(info.rgb, SPHERE_EMISSIVE_FACTOR);
	info.specular_chance = SPHERE_SPECULAR_CHANCE;
	info.specular_roughness = SPHERE_SPECULAR_ROUGHNESS;
	info.index_of_refraction = SPHERE_INDEX_OF_REFRACTION;
	info.refraction_chance = SPHERE_REFRACTION_CHANCE;
	info.refraction_roughness = SPHERE_REFRACTION_ROUGHNESS;
	return (info);
}
