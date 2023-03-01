/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_get_ray_point.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbenneko <vbenneko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 16:34:22 by vbenneko      #+#    #+#                 */
/*   Updated: 2023/01/24 16:35:39 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	rt_get_ray_point(t_ray ray, float t)
{
	return ((t_vector){
		.x = ray.pos.x + (t * ray.dir.x),
		.y = ray.pos.y + (t * ray.dir.y),
		.z = ray.pos.z + (t * ray.dir.z)
	});
}
