/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_line_rgb.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/10 15:22:51 by sbos          #+#    #+#                 */
/*   Updated: 2023/03/10 15:22:51 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	rt_get_line_rgb(t_ray ray, t_hit_info info, t_object object)
{
	(void)ray;
	(void)object;
	return (info.material.rgb);
}
