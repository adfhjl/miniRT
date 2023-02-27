/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_get_vector.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/10 19:51:59 by sbos          #+#    #+#                 */
/*   Updated: 2023/02/10 19:51:59 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	rt_get_vector(float x, float y, float z)
{
	return ((t_vector){.x = x, .y = y, .z = z});
}
