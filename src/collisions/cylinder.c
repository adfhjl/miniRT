/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbenneko <vbenneko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/03 17:12:17 by vbenneko      #+#    #+#                 */
/*   Updated: 2023/02/03 17:17:52 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit_info	rt_get_cylinder_collision_info(
	t_ray ray, t_object *object, t_data *data)
{
	(void)ray;
	(void)object;
	(void)data;
	return ((t_hit_info){.distance = INFINITY});
}
