/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_dirs.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/16 18:55:06 by sbos          #+#    #+#                 */
/*   Updated: 2023/03/16 18:55:06 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rt_structs.h"

#include "rgb/rt_rgb.h"
#include "utils/rt_utils.h"
#include "vectors/rt_vectors.h"

#include <math.h>

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

t_vector	rt_get_refraction_ray_dir(t_hit_info info, t_ray ray,
				float *do_specular, float *do_refraction)
{
	float		eta;
	t_vector	refraction_ray_dir;
	float		t;
	t_vector	diffuse_ray_dir;

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

// Note how the specular ray direction doesn't call random().
// This means it'll always go the same direction.
void	rt_get_diffuse_and_specular_ray_dir(t_vector *diffuse_ray_dir,
			t_vector *specular_ray_dir, t_hit_info info, t_ray ray)
{
	float	t;

	*diffuse_ray_dir = rt_normalized(
			rt_add(info.surface_normal, rt_random_unit_vector()));
	*specular_ray_dir = rt_reflect(ray.dir, info.surface_normal);
	t = info.material.specular_roughness * info.material.specular_roughness;
	*specular_ray_dir = rt_normalized(
			rt_mix(*specular_ray_dir, *diffuse_ray_dir, t));
}
