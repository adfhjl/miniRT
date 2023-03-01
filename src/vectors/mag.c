/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mag.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbenneko <vbenneko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 16:42:37 by vbenneko      #+#    #+#                 */
/*   Updated: 2023/02/13 16:09:50 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#include "vectors/rt_vectors.h"

float	rt_mag2(t_vector v)
{
	return (rt_dot(v, v));
}

float	rt_mag(t_vector v)
{
	return (sqrtf(rt_mag2(v)));
}
