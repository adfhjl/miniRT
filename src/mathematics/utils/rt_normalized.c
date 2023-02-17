/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_normalized.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbenneko <vbenneko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 16:45:30 by vbenneko      #+#    #+#                 */
/*   Updated: 2023/01/24 16:46:02 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mathematics/utils/rt_mathematics_utils.h"

t_vector	rt_normalized(t_vector v)
{
	return (rt_scale(v, 1 / rt_mag(v)));
}
