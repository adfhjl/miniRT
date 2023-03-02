/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add.c                                              :+:    :+:            */
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
		a.x + b.x,
		a.y + b.y,
		a.z + b.z
	});
}
