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

static t_rgb	rt_apply_ambient(t_rgb rgb, t_object *ambient,
					t_vector throughput)
{
	t_rgb	ambient_rgb;

	ambient_rgb = rt_scale(ambient->material.rgb, ambient->ratio);
	return (rt_add(rgb, rt_multiply_rgb(ambient_rgb, throughput)));
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

static t_rgb	rt_update_throughput(float do_refraction, t_rgb rgb,
					float do_specular, t_rgb throughput)
{
	t_rgb	white;
	t_rgb	throughput_factor;

	white = (t_rgb){1, 1, 1};
	if (do_refraction == 0.0f)
	{
		throughput_factor = rt_mix(rgb, white, do_specular);
		throughput = rt_multiply_rgb(throughput, throughput_factor);
	}
	return (throughput);
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

static void	rt_update_ray_dir(t_ray *ray, t_bouncing *b)
{
	t_vector	diffuse_ray_dir;
	t_vector	specular_ray_dir;
	t_vector	refraction_ray_dir;

	rt_get_diffuse_and_specular_ray_dir(&diffuse_ray_dir, &specular_ray_dir, b->info, *ray);
	refraction_ray_dir = rt_get_refraction_ray_dir(b->info, *ray, &b->do_specular, &b->do_refraction);
	// The boolean check is what causes specular highlights.
	ray->dir = rt_mix(diffuse_ray_dir, specular_ray_dir, b->do_specular);
	rt_assert_normal(ray->dir, "h");
	ray->dir = rt_mix(ray->dir, refraction_ray_dir, b->do_refraction);
	rt_assert_normal(ray->dir, "i");
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

static void	rt_update_specular_and_refraction_chances(t_bouncing *b, float *specular_chance,
				float *refraction_chance, t_ray ray, t_hit_info info)
{
	float	n1;
	float	n2;
	float	chance_multiplier;

	b->specular_chance = b->info.material.specular_chance;
	b->refraction_chance = b->info.material.refraction_chance;
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

// Uses Beer's law to get a multiplier for light that travels
// through the object, to make that light decrease:
// multiplier = e^(-absorb * distance)
static t_rgb	rt_absorb(t_bouncing b)
{
	t_rgb	white;
	t_rgb	absorb;
	t_rgb	multiplier;

	white = (t_rgb){1, 1, 1};
	absorb = rt_sub(white, b.info.material.rgb);
	multiplier = rt_exp_rgb(rt_scale(absorb, -b.info.distance));
	return (rt_multiply_rgb(b.throughput, multiplier));
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

static bool	rt_bounce(t_bouncing *b, t_ray *ray, t_data *data)
{
	b->info = rt_get_hit_info(*ray, data);

	if (b->info.distance == INFINITY)
	{
		b->rgb = rt_add(b->rgb, rt_multiply_rgb(b->background, b->throughput));
		return (true);
	}



	// Does absorption if we are hitting from inside the object.
	if (b->info.inside)
		b->throughput = rt_absorb(*b);



	rt_update_specular_and_refraction_chances(b, &b->specular_chance, &b->refraction_chance, *ray, b->info);




	b->do_specular = 0.0f;
	b->do_refraction = 0.0f;
	b->ray_probability = rt_get_ray_action(&b->do_specular, &b->do_refraction, b->specular_chance, b->refraction_chance);



	rt_update_ray_pos(ray, b->info, b->do_refraction);



	rt_update_ray_dir(ray, b);



	b->rgb = rt_add(b->rgb, rt_multiply_rgb(b->info.material.emissive, b->throughput));



	b->throughput = rt_update_throughput(b->do_refraction, b->info.material.rgb, b->do_specular, b->throughput);



	// Since we chose randomly between diffuse and specular,
	// we need to account for the times we didn't do one or the other.
	b->throughput = rt_scale(b->throughput, 1.0f / b->ray_probability);



	if (rt_russian_roulette(&b->throughput))
		return (true);



	b->rgb = rt_apply_ambient(b->rgb, data->ambient, b->throughput);



	return (false);
}

t_rgb	rt_get_ray_rgb(t_ray ray, t_data *data)
{
	t_bouncing	b;
	size_t		bounce_index;

	b.rgb = (t_rgb){0, 0, 0};
	b.throughput = (t_rgb){1, 1, 1};
	b.background = rt_srgb_to_linear(
			(t_rgb){BACKGROUND_R, BACKGROUND_G, BACKGROUND_B});
	bounce_index = 0;
	while (bounce_index <= MAX_BOUNCES_PER_RAY)
	{
		if (rt_bounce(&b, &ray, data))
			break ;
		bounce_index++;
	}
	return (b.rgb);
}
