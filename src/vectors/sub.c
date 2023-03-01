/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sub.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbenneko <vbenneko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 16:40:24 by vbenneko      #+#    #+#                 */
/*   Updated: 2023/01/24 16:40:38 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	rt_sub(t_vector a, t_vector b)
{
	return ((t_vector){
		.x = a.x - b.x,
		.y = a.y - b.y,
		.z = a.z - b.z
	});
}
