/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_get_ray_rgb.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbenneko <vbenneko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 17:15:53 by vbenneko      #+#    #+#                 */
/*   Updated: 2023/02/09 18:21:49 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
		return (rt_get_plane_point_rgb(ray, info, data));
	return ((t_rgb){.r = BACKGROUND_R / 255.0f, .g = BACKGROUND_G / 255.0f,
		.b = BACKGROUND_B / 255.0f});
}
