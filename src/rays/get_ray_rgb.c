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

#include "libft/src/vector/ft_vector.h"

#include "rt_non_bonus_defines.h" // TODO: REMOVE
#include "rt_structs.h"

#include "collisions/rt_collisions.h"
#include "vectors/rt_vectors.h"
#include "rays/rt_rays.h"
#include "rgb/rt_rgb.h"
#include "utils/rt_utils.h"

#include "debug/rt_debug.h" // TODO: REMOVE

#include <math.h>

static float	rt_fresnel_reflect_amount(float n1, float n2, t_vector normal,
					t_vector incident, float f0, float f90)
{
	// Schlick aproximation.
	float r0 = (n1-n2) / (n1+n2);
	r0 *= r0;
	float cosX = -rt_dot(normal, incident);
	if (n1 > n2)
	{
		float n = n1/n2;
		float sinT2 = n*n*(1.0f-cosX*cosX);
		// Total internal reflection.
		if (sinT2 > 1.0f)
			return (f90);
		cosX = sqrtf(1.0f-sinT2);
	}
	float x = 1.0f-cosX;
	float ret = r0+(1.0f-r0)*x*x*x*x*x;

	// adjust reflect multiplier for object reflectivity.
	return (rt_lerp(f0, f90, ret));
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

static t_hit_info	rt_get_hit_info(t_ray ray, t_data *data)
{
	t_hit_info	info;
	size_t		i;

	info.distance = INFINITY;
	i = 0;
	while (i < ft_vector_get_size(data->objects))
	{
		if (data->objects[i].type == OBJECT_TYPE_PLANE)
			rt_get_plane_collision_info(ray, data->objects[i], &info);
		else if (data->objects[i].type == OBJECT_TYPE_SPHERE
			|| data->objects[i].type == OBJECT_TYPE_LIGHT)
			rt_get_sphere_collision_info(ray, data->objects[i], &info);
		else if (data->objects[i].type == OBJECT_TYPE_CYLINDER)
			rt_get_cylinder_collision_info(ray, data->objects[i], &info);
		i++;
	}
	return (info);
}

t_rgb	rt_get_ray_rgb(t_ray ray, t_data *data)
{
	t_rgb		rgb;
	t_rgb		background;
	t_rgb		throughput;
	t_hit_info	info;
	size_t		bounce_index;

	rgb = (t_rgb){0, 0, 0};
	background = rt_srgb_to_linear((t_rgb){BACKGROUND_R, BACKGROUND_G, BACKGROUND_B});
	throughput = (t_rgb){1, 1, 1};

	bounce_index = 0;
	while (bounce_index <= MAX_BOUNCES_PER_RAY)
	{
		// TODO: Don't shoot rays to pixels that immediately had info.distance == INFINITY
		info = rt_get_hit_info(ray, data);

		if (info.distance == INFINITY)
		{
			rgb = rt_add(rgb, rt_multiply_rgb(background, throughput));
			break ;
		}

		// Do absorption if we are hitting from inside the object.
		if (info.inside)
		{
			throughput = rt_multiply_rgb(throughput, rt_exp_rgb(rt_scale(rt_sub((t_vector){1, 1, 1}, info.material.rgb), -info.distance)));
		}

		float	specular_chance;
		float	refraction_chance;

		specular_chance = info.material.specular_chance;
		refraction_chance = info.material.refraction_chance;

		if (specular_chance > 0.0f)
		{
			specular_chance = rt_fresnel_reflect_amount(
				info.inside ? info.material.index_of_refraction : 1.0f,
				!info.inside ? info.material.index_of_refraction : 1.0f,
				ray.dir, info.surface_normal, info.material.specular_chance, 1.0f);

			float chance_multiplier;
			chance_multiplier = (1.0f - specular_chance) / (1.0f - info.material.specular_chance);
			refraction_chance *= chance_multiplier;
		}

		float	do_specular;
		float	do_refraction;
		float	ray_select_roll;
		float	ray_probability;
		do_specular = 0.0f;
		do_refraction = 0.0f;
		ray_select_roll = rt_random_float_01();

		if (specular_chance > 0.0f && ray_select_roll < specular_chance)
		{
			do_specular = 1.0f;
			ray_probability = specular_chance;
		}
		else if (refraction_chance > 0.0f && ray_select_roll < specular_chance + refraction_chance)
		{
			do_refraction = 1.0f;
			ray_probability = refraction_chance;
		}
		else
		{
			ray_probability = 1.0f - (specular_chance + refraction_chance);
		}

		// avoid numerical issues causing a divide by zero, or nearly so (more important later, when we add refraction)
		ray_probability = rt_max(ray_probability, 0.001f);

		ray.pos = rt_add(ray.pos, rt_scale(ray.dir, info.distance));
		// TODO: Using surface_normal here may be wrong. The original code has an if-statement for + or -.
		if (do_refraction == 1.0f)
		{
			ray.pos = rt_add(ray.pos, rt_scale(info.surface_normal, -SURFACE_NORMAL_NUDGE));
		}
		else
		{
			ray.pos = rt_add(ray.pos, rt_scale(info.surface_normal, SURFACE_NORMAL_NUDGE));
		}

		// Calculate the diffuse and specular ray directions.
		t_vector	diffuse_ray_dir;
		diffuse_ray_dir = rt_normalized(rt_add(info.surface_normal, rt_random_unit_vector()));
		t_vector	specular_ray_dir;
		specular_ray_dir = rt_reflect(ray.dir, info.surface_normal);
		// Note how the specular ray direction doesn't call random().
		// This means it'll always go the same direction.
		specular_ray_dir = rt_normalized(rt_mix(specular_ray_dir, diffuse_ray_dir, info.material.specular_roughness * info.material.specular_roughness));

		t_vector	refraction_ray_dir;
		rt_assert_normal(ray.dir, "e");
		rt_assert_normal(info.surface_normal, "f");
		refraction_ray_dir = rt_refract(ray.dir, info.surface_normal, info.inside ? info.material.index_of_refraction : 1.0f / info.material.index_of_refraction);

		// Total internal reflection has occurred.
		if (refraction_ray_dir.x == 0 && refraction_ray_dir.y == 0 && refraction_ray_dir.z == 0)
		{
			do_specular = 1.0f;
			do_refraction = 0.0f;
		}

		refraction_ray_dir = rt_normalized(rt_mix(refraction_ray_dir, rt_normalized(rt_sub(rt_random_unit_vector(), info.surface_normal)), info.material.refraction_roughness * info.material.refraction_roughness));

		// The boolean check is what causes specular highlights.
		ray.dir = rt_mix(diffuse_ray_dir, specular_ray_dir, do_specular);
		rt_assert_normal(ray.dir, "h");
		ray.dir = rt_mix(ray.dir, refraction_ray_dir, do_refraction);
		rt_assert_normal(ray.dir, "i");

		rgb = rt_add(rgb, rt_multiply_rgb(info.material.emissive, throughput));

		if (do_refraction == 0.0f)
			throughput = rt_multiply_rgb(throughput, rt_mix(info.material.rgb, (t_rgb){1, 1, 1}, do_specular));

		// since we chose randomly between diffuse and specular,
		// we need to account for the times we didn't do one or the other.
		throughput = rt_scale(throughput, 1.0f / ray_probability);

		// Russian roulette.
		float p = rt_max(throughput.r, rt_max(throughput.g, throughput.b));
		if (rt_random_float_01() > p)
			break ;
		throughput = rt_scale(throughput, 1.0f / p);

		rgb = rt_add(rgb, rt_multiply_rgb(rt_scale(data->ambient->material.rgb, data->ambient->ratio), throughput));

		bounce_index++;
	}

	return (rgb);
}
