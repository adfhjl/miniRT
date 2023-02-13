/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_mag.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbenneko <vbenneko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 16:42:37 by vbenneko      #+#    #+#                 */
/*   Updated: 2023/02/13 13:43:47 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	rt_mag(t_vector v)
{
	return (sqrtf(rt_dot(v, v)));
}
