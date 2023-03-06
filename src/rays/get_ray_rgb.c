/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_ray_rgb.c                                      :+:    :+:            */
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
#include "vectors/rt_vectors.h"
#include "rays/rt_rays.h"
#include "rgb/rt_rgb.h"
#include "utils/rt_utils.h"
#include "debug/rt_debug.h" // TODO: REMOVE

static t_hit_info	rt_get_hit_info(t_ray ray, t_data *data)
{
	t_hit_info	hit_info;
	t_hit_info	new_hit_info;
	t_rgb		light_rgb;
	size_t		i;

	hit_info.distance = INFINITY;
	new_hit_info.distance = INFINITY;
	light_rgb = (t_rgb){LIGHT_R, LIGHT_G, LIGHT_B};
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
			if (new_hit_info.distance != INFINITY)
			{
				new_hit_info.emissive = rt_scale(rt_scale(new_hit_info.rgb, data->objects[i].ratio), LIGHT_EMISSIVE_FACTOR);
				new_hit_info.rgb = light_rgb;
			}
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
	return ((t_vector){x, y, z});
}

t_rgb	rt_get_ray_rgb(t_ray ray, t_data *data)
{
	t_rgb		rgb;
	t_rgb		background;
	t_rgb		throughput;
	t_hit_info	hit_info;
	size_t		bounce_index;

	rgb = (t_rgb){0, 0, 0};
	background = rt_srgb_to_linear((t_rgb){BACKGROUND_R, BACKGROUND_G, BACKGROUND_B});
	throughput = (t_rgb){1, 1, 1};

	bounce_index = 0;
	while (bounce_index <= MAX_BOUNCES_PER_RAY)
	{
		// TODO: Don't shoot rays to pixels that immediately had hit_info.distance == INFINITY
		hit_info = rt_get_hit_info(ray, data);

		if (hit_info.distance == INFINITY)
		{
			rgb = rt_add(rgb, rt_multiply_rgb(background, throughput));
			break ;
		}

		ray.pos = rt_add(ray.pos, rt_scale(ray.dir, hit_info.distance));
		ray.pos = rt_add(ray.pos, rt_scale(hit_info.surface_normal, SURFACE_NORMAL_NUDGE));

		float	do_specular;

		do_specular = 0;
		if (rt_random_float_01() < hit_info.specularity)
			do_specular = 1;

		t_vector	diffuse_ray_dir;
		t_vector	specular_ray_dir;

		diffuse_ray_dir = rt_normalized(rt_add(hit_info.surface_normal, rt_random_unit_vector()));
		specular_ray_dir = rt_reflect(ray.dir, hit_info.surface_normal);
		specular_ray_dir = rt_normalized(rt_mix(specular_ray_dir, diffuse_ray_dir, hit_info.roughness * hit_info.roughness));
		ray.dir = rt_mix(diffuse_ray_dir, specular_ray_dir, do_specular);

		rgb = rt_add(rgb, rt_multiply_rgb(hit_info.emissive, throughput));

 		throughput = rt_multiply_rgb(throughput, rt_mix(hit_info.rgb, hit_info.specular_color, do_specular));

		float p = rt_max(throughput.r, rt_max(throughput.g, throughput.b));
		if (rt_random_float_01() > p)
			break ;
		throughput = rt_scale(throughput, 1.0f / p);

		rgb = rt_add(rgb, rt_multiply_rgb(rt_scale(data->ambient->rgb, data->ambient->ratio), throughput));

		bounce_index++;
	}

	return (rgb);
}
