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

#include "rt_structs.h"

t_vector	rt_add_scalar_rgb(t_vector a, float b)
{
	return ((t_vector){
		a.x + b,
		a.y + b,
		a.z + b
	});
}
