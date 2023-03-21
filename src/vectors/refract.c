/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   refract.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 19:32:51 by sbos          #+#    #+#                 */
/*   Updated: 2023/03/08 19:32:51 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rt_structs.h"

#include "vectors/rt_vectors.h"

#include <math.h>

// For the incident vector I and surface normal N, and the
// ratio of indices of refraction eta, return the refraction
// vector.
// The input parameters for the incident vector I and the
// surface normal N must already be normalized to get the
// desired results.
// k < 0.0f if total internal reflection occurred.
t_vector	rt_refract(t_vector incident, t_vector normal, float eta)
{
	float		angle;
	float		k;
	t_vector	l;

	angle = rt_dot(normal, incident);
	k = 1.0f - eta * eta * (1.0f - angle * angle);
	if (k < 0.0f)
		return ((t_vector){0, 0, 0});
	else
	{
		l = rt_scale(normal, (eta * angle + sqrtf(k)));
		return (rt_sub(rt_scale(incident, eta), l));
	}
}
