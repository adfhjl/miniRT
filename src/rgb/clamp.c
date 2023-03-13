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

#include "rt_structs.h"

#include "utils/rt_utils.h"

static float	rt_min(float a, float b)
{
	if (a < b)
		return (a);
	return (b);
}

static float	rt_clamp(float n, float lower, float upper)
{
	return (rt_min(rt_max(n, lower), upper));
}

t_rgb	rt_clamp_rgb(t_rgb a, float lower, float upper)
{
	return ((t_rgb){
		rt_clamp(a.r, lower, upper),
		rt_clamp(a.g, lower, upper),
		rt_clamp(a.b, lower, upper)
	});
}
