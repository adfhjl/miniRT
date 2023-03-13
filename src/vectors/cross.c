/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cross.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbenneko <vbenneko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 16:38:40 by vbenneko      #+#    #+#                 */
/*   Updated: 2023/01/24 16:39:12 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rt_structs.h"

t_vector	rt_cross(t_vector a, t_vector b)
{
	return ((t_vector){
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	});
}
