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
	info.distance = q.solution_negative;
	if (q.solution_negative < 0)
		info.distance = q.solution_positive;
	collision = rt_get_ray_point(ray, info.distance);
	sphere_to_collision = rt_sub(collision, sphere.pos);
	info.surface_normal = rt_normalized(sphere_to_collision);
	if (q.solution_negative < 0)
		info.surface_normal = rt_scale(info.surface_normal, -1);
	info.rgb = sphere.rgb;
	info.emissive = rt_get_rgb(0, 0, 0);
	return (info);
}
