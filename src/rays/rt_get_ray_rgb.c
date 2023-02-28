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

#include "collisions/rt_collisions.h"
#include "get_structs/rt_get_structs.h"
#include "mathematics/rt_mathematics.h"
#include "rays/rt_rays.h"
#include "debug/rt_debug.h" // TODO: REMOVE

static t_hit_info	rt_get_hit_info(t_ray ray, t_data *data)
{
	t_hit_info	hit_info;
	t_hit_info	new_hit_info;
	size_t		i;

	hit_info.distance = INFINITY;
	new_hit_info.distance = INFINITY;
	i = 0;
	while (i < ft_vector_get_size(data->objects))
	{
		if (data->objects[i].type == OBJECT_TYPE_PLANE)
			new_hit_info = rt_get_plane_collision_info(ray, data->objects[i]);
		else if (data->objects[i].type == OBJECT_TYPE_SPHERE)
			new_hit_info = rt_get_sphere_collision_info(ray, data->objects[i]);
		else if (data->objects[i].type == OBJECT_TYPE_CYLINDER)
			new_hit_info = rt_get_cylinder_collision_info(ray, data->objects[i]);
		else if (data->objects[i].type == OBJECT_TYPE_LIGHT)
		{
			new_hit_info = rt_get_sphere_collision_info(ray, data->objects[i]);
			new_hit_info.rgb = rt_scale_rgb(new_hit_info.rgb, data->light->ratio);
			new_hit_info.emissive = rt_scale_rgb(new_hit_info.rgb, LIGHT_BRIGHTNESS_FACTOR);
		}
		// TODO: Shouldn't new_hit_info.distance always be positive anyways?
		// TODO: And right now the "> 0" means hit_info.distance will never be 0; is that intended?
		if (new_hit_info.distance > 0
			&& new_hit_info.distance < hit_info.distance)
			hit_info = new_hit_info;
		i++;
	}
	return (hit_info);
}

// Source:
// https://blog.demofox.org/2020/05/25/
// casual-shadertoy-path-tracing-1-basic-camera-diffuse-emissive/
static t_vector	rt_random_unit_vector(void)
{
	float z = rt_random_float_01() * 2.0f - 1.0f;
	float a = rt_random_float_01() * 2.0f * (float)M_PI;
	float r = sqrtf(1.0f - z * z);
	float x = r * cosf(a);
	float y = r * sinf(a);
	return (rt_get_vector(x, y, z));
}

t_rgb	rt_get_ray_rgb(t_ray ray, t_data *data)
{
	t_rgb		rgb;
	t_rgb		throughput;
	t_hit_info	hit_info;
	t_rgb		background;
	size_t		bounce_index;

	rgb = rt_get_rgb(0, 0, 0);
	throughput = rt_get_rgb(1, 1, 1);
	background = rt_get_rgb(BACKGROUND_R, BACKGROUND_G, BACKGROUND_B);

	bounce_index = 0;
	while (bounce_index <= MAX_BOUNCES_PER_RAY)
	{
		// TODO: Don't shoot rays to pixels that immediately had hit_info.distance == INFINITY
		hit_info = rt_get_hit_info(ray, data);

		if (hit_info.distance == INFINITY)
		{
			rgb = rt_add_rgb(rgb, rt_multiply_rgb(background, throughput));
			break ;
		}

		ray.origin = rt_add(ray.origin, rt_scale(ray.normal, hit_info.distance));
		// TODO: Play around with NUDGE values.
		ray.origin = rt_add(ray.origin, rt_scale(hit_info.surface_normal, NUDGE));

		ray.normal = rt_normalized(rt_add(hit_info.surface_normal, rt_random_unit_vector()));
		rt_assert_normal(ray.normal);

		rgb = rt_add_rgb(rgb, rt_multiply_rgb(hit_info.emissive, throughput));

		throughput = rt_multiply_rgb(throughput, hit_info.rgb);

		bounce_index++;
	}

	return (rgb);
}
