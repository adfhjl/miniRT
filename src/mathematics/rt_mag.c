/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_mag.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbenneko <vbenneko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 16:42:37 by vbenneko      #+#    #+#                 */
/*   Updated: 2023/02/13 16:09:50 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#include "mathematics/rt_mathematics.h"

// ||v|| = sqrt(v.x^2 + v.y^2 + v.z^2) = dot(v, v);
float	rt_mag(t_vector v)
{
	return (sqrtf(rt_dot(v, v)));
}
