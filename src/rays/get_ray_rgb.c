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
#include "vectors/rt_vectors.h"
#include "rays/rt_rays.h"
#include "rgb/rt_rgb.h"
#include "utils/rt_utils.h"
#include "debug/rt_debug.h" // TODO: REMOVE

static float	rt_fresnel_reflect_amount(float n1, float n2, t_vector normal,
					t_vector incident, float f0, float f90)
{
	// Schlick aproximation
	float r0 = (n1-n2) / (n1+n2);
	r0 *= r0;
	float cosX = -rt_dot(normal, incident);
	if (n1 > n2)
	{
		float n = n1/n2;
		float sinT2 = n*n*(1.0f-cosX*cosX);
		// Total internal reflection
		if (sinT2 > 1.0f)
			return (f90);
		cosX = sqrtf(1.0f-sinT2);
	}
	float x = 1.0f-cosX;
	float ret = r0+(1.0f-r0)*x*x*x*x*x;

	// adjust reflect multiplier for object reflectivity
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
			if (new_hit_info.distance != INFINITY)
			{
				// TODO: Can I get rid of LIGHT_EMISSIVE_FACTOR?
				new_hit_info.material.emissive = rt_scale(rt_scale(new_hit_info.material.rgb, data->objects[i].ratio), LIGHT_EMISSIVE_FACTOR);
				// TODO: Can I just set this to the rgb?
				new_hit_info.material.rgb = (t_rgb){LIGHT_R, LIGHT_G, LIGHT_B};
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

		// do absorption if we are hitting from inside the object
		if (hit_info.inside)
		{
			throughput = rt_multiply_rgb(throughput, rt_exp_rgb(rt_scale(rt_sub((t_vector){1, 1, 1}, hit_info.material.rgb), -hit_info.distance)));
		}

		float	specular_chance;
		float	refraction_chance;

		specular_chance = hit_info.material.specular_chance;
		refraction_chance = hit_info.material.refraction_chance;

		if (specular_chance > 0.0f)
		{
			specular_chance = rt_fresnel_reflect_amount(
				hit_info.inside ? hit_info.material.index_of_refraction : 1.0f,
				!hit_info.inside ? hit_info.material.index_of_refraction : 1.0f,
				ray.dir, hit_info.surface_normal, hit_info.material.specular_chance, 1.0f);

			float chance_multiplier;
			chance_multiplier = (1.0f - specular_chance) / (1.0f - hit_info.material.specular_chance);
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

		ray.pos = rt_add(ray.pos, rt_scale(ray.dir, hit_info.distance));
		// TODO: Using surface_normal here may be wrong. The original code has an if-statement for + or -.
		if (do_refraction == 1.0f)
		{
			ray.pos = rt_add(ray.pos, rt_scale(hit_info.surface_normal, -SURFACE_NORMAL_NUDGE));
		}
		else
		{
			ray.pos = rt_add(ray.pos, rt_scale(hit_info.surface_normal, SURFACE_NORMAL_NUDGE));
		}

		// Calculate the diffuse and specular ray directions.
		t_vector	diffuse_ray_dir;
		diffuse_ray_dir = rt_normalized(rt_add(hit_info.surface_normal, rt_random_unit_vector()));
		t_vector	specular_ray_dir;
		specular_ray_dir = rt_reflect(ray.dir, hit_info.surface_normal);
		// Note how the specular ray direction doesn't call random().
		// This means it'll always go the same direction.
		specular_ray_dir = rt_normalized(rt_mix(specular_ray_dir, diffuse_ray_dir, hit_info.material.specular_roughness * hit_info.material.specular_roughness));

		t_vector	refraction_ray_dir;
		refraction_ray_dir = rt_refract(ray.dir, hit_info.surface_normal, hit_info.inside ? hit_info.material.index_of_refraction : 1.0f / hit_info.material.index_of_refraction);
		refraction_ray_dir = rt_normalized(rt_mix(refraction_ray_dir, rt_normalized(rt_sub(rt_random_unit_vector(), hit_info.surface_normal)), hit_info.material.refraction_roughness * hit_info.material.refraction_roughness));

		// The boolean check is what causes specular highlights.
		ray.dir = rt_mix(diffuse_ray_dir, specular_ray_dir, do_specular);
		ray.dir = rt_mix(ray.dir, refraction_ray_dir, do_refraction);

		rgb = rt_add(rgb, rt_multiply_rgb(hit_info.material.emissive, throughput));

		if (do_refraction == 0.0f)
			throughput = rt_multiply_rgb(throughput, rt_mix(hit_info.material.rgb, (t_rgb){1, 1, 1}, do_specular));

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
