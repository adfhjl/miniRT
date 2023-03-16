/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_ray_endpoint.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbenneko <vbenneko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 16:34:22 by vbenneko      #+#    #+#                 */
/*   Updated: 2023/01/24 16:35:39 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rt_structs.h"

t_vector	rt_get_ray_endpoint(t_ray ray, float t)
{
	return ((t_vector){
		ray.pos.x + (t * ray.dir.x),
		ray.pos.y + (t * ray.dir.y),
		ray.pos.z + (t * ray.dir.z)
	});
}
