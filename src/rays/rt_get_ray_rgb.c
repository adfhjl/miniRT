/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_get_ray_rgb.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbenneko <vbenneko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 17:15:53 by vbenneko      #+#    #+#                 */
/*   Updated: 2023/02/23 17:55:58 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#include "mathematics/rt_mathematics.h"
#include "collisions/rt_collisions.h"
#include "rays/rt_rays.h"

t_hit_info	rt_get_hit_info(t_ray ray, t_data *data)
{
	t_hit_info	hit_info;
	t_hit_info	tmp;
	size_t		i;

	hit_info.distance = INFINITY;
	tmp.distance = INFINITY;
	i = 0;
	while (i < ft_vector_get_size(data->objects))
	{
		if (data->objects[i].type == OBJECT_TYPE_PLANE)
			tmp = rt_get_plane_collision_info(ray, &data->objects[i]);
		else if (data->objects[i].type == OBJECT_TYPE_SPHERE)
			tmp = rt_get_sphere_collision_info(ray, &data->objects[i]);
		else if (data->objects[i].type == OBJECT_TYPE_CYLINDER)
			tmp = rt_get_cylinder_collision_info(ray, &data->objects[i]);
		// TODO: Shouldn't tmp.distance always be positive anyways?
		// TODO: And right now the "> 0" means hit_info.distance will never be 0; is that intended?
		if (tmp.distance > 0 && tmp.distance < hit_info.distance)
			hit_info = tmp;
		i++;
	}
	return (hit_info);
}

static t_vector	rt_rotate_around_axis(t_vector v, t_vector rotation_axis,
				float theta)
{
	return (rt_add(rt_add(rt_scale(v, cosf(theta)),
	rt_scale(rt_cross(rotation_axis, v), sinf(theta))),
	rt_scale(rotation_axis, rt_dot(rotation_axis, v) * (1 - cosf(theta)))));
}

t_rgb	rt_get_ray_rgb(t_ray ray, t_data *data, int depth)
{
	t_hit_info	info;
	t_rgb		rgb;

	info = rt_get_hit_info(ray, data);
	if (info.distance == INFINITY)
		return ((t_rgb){.r = BACKGROUND_R / 255.0f,
			.g = BACKGROUND_G / 255.0f, .b = BACKGROUND_B / 255.0f});
	if (info.object->type == OBJECT_TYPE_PLANE)
		rgb = rt_get_point_rgb(ray, info, data, info.object->plane.rgb);
	if (info.object->type == OBJECT_TYPE_SPHERE)
		rgb = rt_get_point_rgb(ray, info, data, info.object->sphere.rgb);
	if (info.object->type == OBJECT_TYPE_CYLINDER)
		rgb = rt_get_point_rgb(ray, info, data, info.object->cylinder.rgb);
	if (depth == MAX_BOUNCES_PER_RAY || data->reflection_ratio == 0)
		return (rgb);
	// return (rt_add_rgb(rt_scale_rgb(rgb, 1 - data->reflection_ratio), rt_scale_rgb(rt_get_ray_rgb(rt_get_ray(rt_add(rt_get_ray_point(ray, info.distance), rt_scale(info.surface_normal, EPSILON * 100)), rt_rotate_around_axis(rt_scale(ray.normal, -1), info.surface_normal, (float)M_PI)), data, depth + 1), data->reflection_ratio)));
	return (rt_add_rgb(rt_scale_rgb(rgb, 1 - data->reflection_ratio), rt_scale_rgb(rt_get_ray_rgb(rt_get_ray(rt_add(rt_get_ray_point(ray, info.distance), rt_scale(info.surface_normal, EPSILON * 100 * -fabsf(rt_dot(info.surface_normal, ray.normal)) / rt_dot(info.surface_normal, ray.normal))), rt_rotate_around_axis(rt_scale(ray.normal, -1), info.surface_normal, (float)M_PI)), data, depth + 1), data->reflection_ratio)));
}
