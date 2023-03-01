/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   scale.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbenneko <vbenneko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 16:41:00 by vbenneko      #+#    #+#                 */
/*   Updated: 2023/02/01 17:15:08 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	rt_scale(t_vector v, float f)
{
	return ((t_vector){
		.x = v.x * f,
		.y = v.y * f,
		.z = v.z * f
	});
}
