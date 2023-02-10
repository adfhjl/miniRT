/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_get_ray.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/10 19:51:59 by sbos          #+#    #+#                 */
/*   Updated: 2023/02/10 19:51:59 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	rt_get_ray(t_vector origin, t_vector normal)
{
	return ((t_ray){.origin=origin, .normal=normal});
}
