/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clamp.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/03 18:24:22 by sbos          #+#    #+#                 */
/*   Updated: 2023/03/03 18:24:22 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static float	rt_min(float a, float b)
{
	if (a < b)
		return (a);
	return (b);
}

static float	rt_max(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}

t_rgb	rt_clamp_rgb(t_rgb a, float lower, float upper)
{
	return ((t_rgb){
		rt_min(rt_max(a.r, lower), upper),
		rt_min(rt_max(a.g, lower), upper),
		rt_min(rt_max(a.b, lower), upper)
	});
}
