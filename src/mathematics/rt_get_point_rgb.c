/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_get_point_rgb.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbenneko <vbenneko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/14 14:05:25 by vbenneko      #+#    #+#                 */
/*   Updated: 2023/02/14 14:43:10 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_rgb	rt_clamp_rgb(t_rgb rgb)
{
	return ((t_rgb){
		.r = fminf(rgb.r, 1.0),
		.g = fminf(rgb.g, 1.0),
		.b = fminf(rgb.b, 1.0)
	});
}

// The light_distance_factor is based on the inverse-square law
static t_rgb	rt_get_rgb_factor(t_ray ray, t_hit_info info, t_hit_info light_ray_info,
		t_vector biased_point_to_light, t_data *data)
{
	const t_rgb			scaled_ambient
		= rt_scale_rgb(data->ambient->rgb, data->ambient->ratio);
	const t_vector		collision_point_to_light
		= rt_sub(data->light->origin, rt_get_ray_point(ray, info.distance));
	const float			light_angle_rgb_factor
		= rt_dot(rt_normalized(collision_point_to_light), info.surface_normal);
	const float			light_distance_factor
		= 1 / rt_dot(biased_point_to_light, biased_point_to_light);

	if (info.visibility == BLOCKED
	|| light_ray_info.distance < rt_mag(biased_point_to_light))
		return (scaled_ambient);
	else
	{
		// TODO: dutch-flag.rt has wrong shadowing at the top and bottom, so something is fucky wucky here
		assert(light_angle_rgb_factor > 0); // TODO: Remove once we know for certain this will never happen
		return (rt_add_rgb(scaled_ambient, rt_scale_rgb(data->light->rgb,
					data->light->brightness * light_angle_rgb_factor
					* light_distance_factor * LIGHT_BRIGHTNESS_FACTOR)));
	}
}

// C = camera ray normal, N = object normal
// C N
// ^ ^ = V // if (dot(c.normal, p.normal) > 0) return scale(p.normal, -1)
// V ^ = ^ // return (p.normal)
// ^ V = V // return (p.normal)
// V V = ^ // if (dot(c.normal, p.normal) > 0) return scale(p.normal, -1)
static t_vector	rt_get_bias_unit_vector(t_vector camera_normal, t_vector object_normal)
{
	if (rt_dot(camera_normal, object_normal) > 0)
		return (rt_scale(object_normal, -1));
	return (object_normal);
}

t_rgb	rt_get_point_rgb(t_ray ray, t_hit_info info, t_data *data,
	t_rgb object_color)
{
	const t_vector		biased_point = rt_get_ray_point(rt_get_ray(
				rt_get_ray_point(ray, info.distance),
				rt_get_bias_unit_vector(ray.normal, info.surface_normal)),
			(float)EPSILON * 100);
	const t_hit_info	light_ray_info = rt_get_hit_info(rt_get_ray(
				biased_point,
				rt_normalized(rt_sub(data->light->origin, biased_point))),
			data);
	const t_vector		biased_point_to_light
		= rt_sub(data->light->origin, biased_point);

	return (rt_clamp_rgb(rt_multiply_rgb(object_color,
				rt_get_rgb_factor(ray, info, light_ray_info,
					biased_point_to_light, data))));
}

// rgb=$pl_RGB * ($A_RGB * $A_LVL + $l_RGB * $l_LVL * $l_DST)
// rgb=$pl_RGB * ($A_RGB * $A_LVL) + $pl_RGB * ($l_RGB * $l_LVL * $l_DST)
