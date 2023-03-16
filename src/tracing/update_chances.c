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

void	rt_update_specular_and_refraction_chances(float *specular_chance,
			float *refraction_chance, t_ray ray, t_hit_info info)
{
	float	n1;
	float	n2;
	float	chance_multiplier;

	*specular_chance = info.material.specular_chance;
	*refraction_chance = info.material.refraction_chance;
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
