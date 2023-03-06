/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reflect.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/06 12:44:24 by sbos          #+#    #+#                 */
/*   Updated: 2023/03/06 12:44:24 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#include "vectors/rt_vectors.h"

// Where d is the incoming ray's normal, n is the surface normal,
// and r is the outgoing ray's normal.
// r = d - n * 2 * dot(d, n)
// Note that n must be normalized!
// Source: https://math.stackexchange.com/a/13263/1156398
t_vector	rt_reflect(t_vector d, t_vector n)
{
	return (rt_sub(d, rt_scale(n, 2 * rt_dot(d, n))));
}
