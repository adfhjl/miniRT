/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mix.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/06 13:11:34 by sbos          #+#    #+#                 */
/*   Updated: 2023/03/06 13:11:34 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rt_structs.h"

#include "utils/rt_utils.h"

t_rgb	rt_mix(t_rgb a, t_rgb b, float t)
{
	return ((t_rgb){
		rt_lerp(a.r, b.r, t),
		rt_lerp(a.g, b.g, t),
		rt_lerp(a.b, b.b, t),
	});
}
