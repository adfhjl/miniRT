/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_get_ray_rgb.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbenneko <vbenneko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 17:15:53 by vbenneko      #+#    #+#                 */
/*   Updated: 2023/02/14 14:08:35 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#include "mathematics/rt_mathematics.h"
#include "collisions/rt_collisions.h"
#include "rays/rt_rays.h"

// TODO: Victor, welke scene maakt dit een drastisch visueel verschil voor?
// Bij scenes/valid/light-under-plane.rt ziet altijd VISIBLE returnen er hetzelfde uit
//
// N = surface normal, C = camera ray normal, L = light ray normal
// N C L
// ^ v ^ -> false == true -> VISIBLE
// v v ^ -> true == false -> VISIBLE
// v ^ v -> false == true -> VISIBLE
// ^ ^ v -> true == false -> VISIBLE
// ^ v v -> false == false -> BLOCKED
// ^ ^ ^ -> true == true -> BLOCKED
t_visibility	rt_get_visibility(t_hit_info info, t_ray camera_ray,
					t_light *light)
{
	const bool		surface_and_camera_rays_point_in_same_direction
		= rt_dot(info.surface_normal, camera_ray.normal) > 0;
	const t_vector	light_ray_normal
		= rt_sub(light->origin, rt_get_ray_point(camera_ray, info.distance));
	const bool		surface_and_light_rays_point_in_same_direction
		= rt_dot(info.surface_normal, light_ray_normal) > 0;

	if (surface_and_camera_rays_point_in_same_direction
		== surface_and_light_rays_point_in_same_direction)
		return (BLOCKED);
	return (VISIBLE);
}

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
			tmp = rt_get_plane_collision_info(ray, &data->objects[i], data);
		else if (data->objects[i].type == OBJECT_TYPE_SPHERE)
			tmp = rt_get_sphere_collision_info(ray, &data->objects[i], data);
		else if (data->objects[i].type == OBJECT_TYPE_CYLINDER)
			tmp = rt_get_cylinder_collision_info(ray, &data->objects[i], data);
		// TODO: Shouldn't tmp.distance always be positive anyways?
		// TODO: And right now the "> 0" means hit_info.distance will never be 0; is that intended?
		if (tmp.distance > 0 && tmp.distance < hit_info.distance)
			hit_info = tmp;
		i++;
	}
	return (hit_info);
}

t_rgb	rt_get_ray_rgb(t_ray ray, t_data *data)
{
	t_hit_info	info;

	info = rt_get_hit_info(ray, data);
	if (info.distance == INFINITY)
		return ((t_rgb){.r = BACKGROUND_R / 255.0f,
			.g = BACKGROUND_G / 255.0f, .b = BACKGROUND_B / 255.0f});
	if (info.object->type == OBJECT_TYPE_PLANE)
		return (rt_get_point_rgb(ray, info, data, info.object->plane.rgb));
	if (info.object->type == OBJECT_TYPE_SPHERE)
		return (rt_get_point_rgb(ray, info, data, info.object->sphere.rgb));
	return ((t_rgb){.r = BACKGROUND_R / 255.0f, .g = BACKGROUND_G / 255.0f,
		.b = BACKGROUND_B / 255.0f});
}
