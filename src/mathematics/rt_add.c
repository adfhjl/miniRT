/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_add.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbenneko <vbenneko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 16:39:47 by vbenneko      #+#    #+#                 */
/*   Updated: 2023/02/06 15:30:50 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	rt_add(t_vector a, t_vector b)
{
	return ((t_vector){
		.x = a.x + b.x,
		.y = a.y + b.y,
		.z = a.z + b.z
	});
}

t_rgb	rt_add_rgb(t_rgb a, t_rgb b)
{
	return ((t_rgb){
		.r = a.r + b.r,
		.g = a.g + b.g,
		.b = a.b + b.b
	});
}
