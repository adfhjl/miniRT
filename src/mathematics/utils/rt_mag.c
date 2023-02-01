/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_mag.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbenneko <vbenneko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 16:42:37 by vbenneko      #+#    #+#                 */
/*   Updated: 2023/01/24 16:45:48 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	rt_mag(t_vector v)
{
	return (sqrtf(rt_mag2(v)));
}
