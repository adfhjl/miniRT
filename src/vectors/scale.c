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

#include "rt_structs.h"

t_vector	rt_scale(t_vector v, float f)
{
	return ((t_vector){
		v.x * f,
		v.y * f,
		v.z * f
	});
}
