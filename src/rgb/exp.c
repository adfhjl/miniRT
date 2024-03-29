/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exp_rgb.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/08 19:06:48 by sbos          #+#    #+#                 */
/*   Updated: 2023/03/08 19:06:48 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rt_structs.h"

#include <math.h>

t_rgb	rt_exp_rgb(t_rgb rgb)
{
	return ((t_rgb){
		expf(rgb.r),
		expf(rgb.g),
		expf(rgb.b)
	});
}
