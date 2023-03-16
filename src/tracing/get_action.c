/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_action.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/16 18:54:31 by sbos          #+#    #+#                 */
/*   Updated: 2023/03/16 18:54:31 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils/rt_utils.h"

float	rt_get_ray_action(float *do_specular, float *do_refraction,
					float specular_chance, float refraction_chance)
{
	float	ray_select_roll;
	float	ray_probability;

	*do_specular = 0.0f;
	*do_refraction = 0.0f;
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
