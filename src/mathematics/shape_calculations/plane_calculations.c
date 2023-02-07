/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane_calculations.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbenneko <vbenneko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/03 17:08:36 by vbenneko      #+#    #+#                 */
/*   Updated: 2023/02/06 19:02:45 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit_info	rt_get_plane_collision_info(
	t_ray ray, t_object *object, t_data *data)
{
	t_hit_info		info;
	const t_plane	plane = object->plane;
	float			n;

	n = rt_dot(ray.direction, plane.orientation);
	if (n == 0)
		return ((t_hit_info){.distance = INFINITY});
	info.distance = (1 / n) * (rt_dot(plane.coordinates, plane.orientation)
			- rt_dot(ray.origin, plane.orientation));
	info.object = object;
	info.surface_normal = plane.orientation;
	info.visual_surface_normal = 1;
	if ((rt_dot(info.surface_normal, ray.direction) > 0) != \
		(rt_dot(info.surface_normal, \
			rt_normalized(rt_sub(data->light->coordinates, \
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

t_rgb	rt_get_plane_point_rgb(t_ray ray, t_hit_info info, t_data *data)
{
	const t_vector		point_to_light = rt_sub(data->light->coordinates,
			rt_get_ray_point(ray, info.distance));
	const t_hit_info	light_ray_info = rt_get_hit_info((t_ray){
			.origin = rt_get_ray_point(ray, info.distance),
			.direction = point_to_light}, data);

	if (info.visual_surface_normal == -1 \
	|| light_ray_info.distance < rt_mag(point_to_light))
		return (rt_multiply_rgb(info.object->plane.rgb,
				rt_scale_rgb(data->ambient->rgb, data->ambient->ratio)));
	return (rt_clamp_rgb(rt_multiply_rgb(info.object->plane.rgb, rt_add_rgb(
					rt_scale_rgb(data->ambient->rgb, data->ambient->ratio),
					rt_scale_rgb((t_rgb){.r = 1, .g = 1, .b = 1},
					data->light->brightness * 1.0f))))); // replace `1.0f` with some distance factor
}

// Add RGB lighting?
	// return (rt_clamp_rgb(rt_multiply_rgb(info.object->plane.rgb, rt_add_rgb(
	// 				rt_scale_rgb(data->ambient->rgb, data->ambient->ratio),
	// 				rt_scale_rgb(data->light->rgb,
	// 					data->light->brightness * 1.0f))))); // replace `1.0f` with some distance factor
// rgb=$pl_RGB * ($A_RGB * $A_LVL + $l_RGB * $l_LVL * $l_DST)
