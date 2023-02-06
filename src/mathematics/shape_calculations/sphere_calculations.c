/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere_calculations.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbenneko <vbenneko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/03 17:11:26 by vbenneko      #+#    #+#                 */
/*   Updated: 2023/02/03 17:19:07 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// TODO: Make this function
t_hit_info	rt_get_sphere_collision_info(
	t_ray ray, t_object *object, t_data *data)
{
	(void)ray;
	(void)object;
	(void)data;
	return ((t_hit_info){.distance = INFINITY});
}
