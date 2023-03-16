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
	float	r0;
	float	cos_x;
	float	n;
	float	sin_t2;
	float	x;
	float	ret;

	// Schlick aproximation.
	r0 = (n1 - n2) / (n1 + n2);
	r0 *= r0;
	cos_x = -rt_dot(normal, incident);
	if (n1 > n2)
	{
		n = n1 / n2;
		sin_t2 = n * n * (1.0f - cos_x * cos_x);
		// Total internal reflection.
		if (sin_t2 > 1.0f)
			return (f90);
		cos_x = sqrtf(1.0f - sin_t2);
	}
	x = 1.0f - cos_x;
	ret = r0 + (1.0f - r0) * x * x * x * x * x;
	// Adjust reflect multiplier for object reflectivity.
	return (rt_lerp(f0, f90, ret));
}

static bool	rt_russian_roulette(t_vector *throughput)
{
	float	p;

	p = rt_max(throughput->r, rt_max(throughput->g, throughput->b));
	if (rt_random_float_01() > p)
		return (true);
	*throughput = rt_scale(*throughput, 1.0f / p);
	return (false);
}

// Source:
// https://blog.demofox.org/2020/05/25/
// casual-shadertoy-path-tracing-1-basic-camera-diffuse-emissive/
static t_vector	rt_random_unit_vector(void)
{
	float	z;
	float	a;
	float	r;
	float	x;
	float	y;

	z = rt_random_float_01() * 2.0f - 1.0f;
	a = rt_random_float_01() * 2.0f * (float)M_PI;
	r = sqrtf(1.0f - z * z);
	x = r * cosf(a);
	y = r * sinf(a);
	return ((t_vector){x, y, z});
}

static bool	rt_total_internal_reflection_occurred(t_vector dir)
{
	return (dir.x == 0 && dir.y == 0 && dir.z == 0);
}

static t_vector	rt_get_refraction_ray_dir(t_hit_info info, t_ray ray,
					float *do_specular, float *do_refraction)
{
	float		eta;
	t_vector	refraction_ray_dir;
	float		t;
	t_vector	diffuse_ray_dir;

	rt_assert_normal(ray.dir, "e");
	rt_assert_normal(info.surface_normal, "f");
	eta = 1.0f / info.material.index_of_refraction;
	if (info.inside)
		eta = info.material.index_of_refraction;
	refraction_ray_dir = rt_refract(ray.dir, info.surface_normal, eta);
	if (rt_total_internal_reflection_occurred(refraction_ray_dir))
	{
		*do_specular = 1.0f;
		*do_refraction = 0.0f;
	}
	diffuse_ray_dir = rt_normalized(
			rt_sub(rt_random_unit_vector(), info.surface_normal));
	t = info.material.refraction_roughness * info.material.refraction_roughness;
	return (rt_normalized(rt_mix(refraction_ray_dir, diffuse_ray_dir, t)));
}

static void	rt_get_diffuse_and_specular_ray_dir(t_vector *diffuse_ray_dir,
				t_vector *specular_ray_dir, t_hit_info info, t_ray ray)
{
	float	t;

	*diffuse_ray_dir = rt_normalized(
			rt_add(info.surface_normal, rt_random_unit_vector()));
	*specular_ray_dir = rt_reflect(ray.dir, info.surface_normal);
	// Note how the specular ray direction doesn't call random().
	// This means it'll always go the same direction.
	t = info.material.specular_roughness * info.material.specular_roughness;
	*specular_ray_dir = rt_normalized(
			rt_mix(*specular_ray_dir, *diffuse_ray_dir, t));
}

static void	rt_update_ray_pos(t_ray *ray, t_hit_info info,
				float do_refraction)
{
	float	nudge;

	ray->pos = rt_add(ray->pos, rt_scale(ray->dir, info.distance));
	nudge = SURFACE_NORMAL_NUDGE;
	if (do_refraction == 1.0f)
		nudge *= -1;
	ray->pos = rt_add(ray->pos, rt_scale(info.surface_normal, nudge));
}

static float	rt_get_ray_action(float *do_specular, float *do_refraction,
					float specular_chance, float refraction_chance)
{
	float	ray_select_roll;
	float	ray_probability;

	ray_select_roll = rt_random_float_01();
	if (specular_chance > 0.0f && ray_select_roll < specular_chance)
	{
		*do_specular = 1.0f;
		ray_probability = specular_chance;
	}
	else if (refraction_chance > 0.0f
		&& ray_select_roll < specular_chance + refraction_chance)
	{
		*do_refraction = 1.0f;
		ray_probability = refraction_chance;
	}
	else
		ray_probability = 1.0f - (specular_chance + refraction_chance);
	// Avoids numerical issues causing a divide by zero.
	ray_probability = rt_max(ray_probability, 0.001f);
	return (ray_probability);
}

static void	rt_get_specular_and_refraction_chances(float *specular_chance,
				float *refraction_chance, t_ray ray, t_hit_info info)
{
	float	n1;
	float	n2;
	float	chance_multiplier;

	if (*specular_chance > 0.0f)
	{
		n1 = 1.0f;
		if (info.inside)
			n1 = info.material.index_of_refraction;
		n2 = info.material.index_of_refraction;
		if (info.inside)
			n2 = 1.0f;
		*specular_chance = rt_fresnel_reflect_amount(n1, n2, ray.dir,
				info.surface_normal, info.material.specular_chance, 1.0f);
		chance_multiplier = (1.0f - *specular_chance)
			/ (1.0f - info.material.specular_chance);
		*refraction_chance *= chance_multiplier;
	}
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
	background = rt_srgb_to_linear(
			(t_rgb){BACKGROUND_R, BACKGROUND_G, BACKGROUND_B});
	throughput = (t_rgb){1, 1, 1};

	bounce_index = 0;
	while (bounce_index <= MAX_BOUNCES_PER_RAY)
	{
		info = rt_get_hit_info(ray, data);

		if (info.distance == INFINITY)
		{
			rgb = rt_add(rgb, rt_multiply_rgb(background, throughput));
			break ;
		}

		// Does absorption if we are hitting from inside the object.
		if (info.inside)
			throughput = rt_multiply_rgb(throughput, rt_exp_rgb(rt_scale(rt_sub((t_vector){1, 1, 1}, info.material.rgb), -info.distance)));



		float	specular_chance;
		float	refraction_chance;

		specular_chance = info.material.specular_chance;
		refraction_chance = info.material.refraction_chance;
		rt_get_specular_and_refraction_chances(&specular_chance, &refraction_chance, ray, info);



		float	do_specular;
		float	do_refraction;
		float	ray_probability;

		do_specular = 0.0f;
		do_refraction = 0.0f;
		ray_probability = rt_get_ray_action(&do_specular, &do_refraction, specular_chance, refraction_chance);



		rt_update_ray_pos(&ray, info, do_refraction);



		t_vector	diffuse_ray_dir;
		t_vector	specular_ray_dir;

		rt_get_diffuse_and_specular_ray_dir(&diffuse_ray_dir, &specular_ray_dir, info, ray);



		t_vector	refraction_ray_dir;

		refraction_ray_dir = rt_get_refraction_ray_dir(info, ray, &do_specular, &do_refraction);



		// The boolean check is what causes specular highlights.
		ray.dir = rt_mix(diffuse_ray_dir, specular_ray_dir, do_specular);
		rt_assert_normal(ray.dir, "h");
		ray.dir = rt_mix(ray.dir, refraction_ray_dir, do_refraction);
		rt_assert_normal(ray.dir, "i");



		rgb = rt_add(rgb, rt_multiply_rgb(info.material.emissive, throughput));



		if (do_refraction == 0.0f)
			throughput = rt_multiply_rgb(throughput, rt_mix(info.material.rgb, (t_rgb){1, 1, 1}, do_specular));

		// Since we chose randomly between diffuse and specular,
		// we need to account for the times we didn't do one or the other.
		throughput = rt_scale(throughput, 1.0f / ray_probability);



		if (rt_russian_roulette(&throughput))
			break ;



		rgb = rt_add(rgb, rt_multiply_rgb(rt_scale(data->ambient->material.rgb, data->ambient->ratio), throughput));



		bounce_index++;
	}

	return (rgb);
}
