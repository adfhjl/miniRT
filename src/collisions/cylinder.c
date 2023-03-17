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
#include "utils/rt_utils.h"
#include "vectors/rt_vectors.h"

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
	info->surface_normal = rt_get_cylinder_surface_normal(
			rt_get_ray_endpoint(ray, distance), cylinder);
	info->inside = false;
	info->material = cylinder.material;
	info->material.rgb = rt_get_line_rgb(ray, *info, cylinder);
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
