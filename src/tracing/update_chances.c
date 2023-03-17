/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update_chances.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/16 18:53:19 by sbos          #+#    #+#                 */
/*   Updated: 2023/03/16 18:53:19 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rt_structs.h"

#include "utils/rt_utils.h"
#include "vectors/rt_vectors.h"

#include <math.h>

// https://en.wikipedia.org/wiki/Schlick's_approximation
static float	rt_schlick_approximation(float ior1, float ior2)
{
	float	r0;

	r0 = (ior1 - ior2) / (ior1 + ior2);
	return (r0 * r0);
}

// sin_t2 > 1.0f if total internal reflection occurred.
// The lerp at the end adjusts the reflect multiplier for object reflectivity.
static float	rt_fresnel_reflect_amount(float ior1, float ior2, float cos_x,
					float f0)
{
	float	r0;
	float	n;
	float	sin_t2;
	float	x;

	r0 = rt_schlick_approximation(ior1, ior2);
	if (ior1 > ior2)
	{
		n = ior1 / ior2;
		sin_t2 = n * n * (1.0f - cos_x * cos_x);
		if (sin_t2 > 1.0f)
			return (1.0f);
		cos_x = sqrtf(1.0f - sin_t2);
	}
	x = 1.0f - cos_x;
	return (rt_lerp(f0, 1.0f, r0 + (1.0f - r0) * x * x * x * x * x));
}

void	rt_update_specular_and_refraction_chances(float *specular_chance,
			float *refraction_chance, t_ray ray, t_hit_info info)
{
	float	ior1;
	float	ior2;
	float	chance_multiplier;

	*specular_chance = info.material.specular_chance;
	*refraction_chance = info.material.refraction_chance;
	if (*specular_chance > 0.0f)
	{
		ior1 = 1.0f;
		if (info.inside)
			ior1 = info.material.index_of_refraction;
		ior2 = info.material.index_of_refraction;
		if (info.inside)
			ior2 = 1.0f;
		*specular_chance = rt_fresnel_reflect_amount(ior1, ior2,
				-rt_dot(ray.dir, info.surface_normal),
				info.material.specular_chance);
		chance_multiplier = (1.0f - *specular_chance)
			/ (1.0f - info.material.specular_chance);
		*refraction_chance *= chance_multiplier;
	}
}
