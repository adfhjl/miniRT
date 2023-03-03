/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/01 19:16:17 by sbos          #+#    #+#                 */
/*   Updated: 2023/03/01 19:16:17 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	rt_add_rgb(t_rgb a, t_rgb b)
{
	return ((t_rgb){
		a.r + b.r,
		a.g + b.g,
		a.b + b.b
	});
}

t_vector	rt_add_scalar_rgb(t_vector a, float b)
{
	return ((t_vector){
		a.x + b,
		a.y + b,
		a.z + b
	});
}
