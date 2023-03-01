/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   multiply.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbenneko <vbenneko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/01 16:23:04 by vbenneko      #+#    #+#                 */
/*   Updated: 2023/02/01 17:16:45 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	rt_multiply_rgb(t_rgb a, t_rgb b)
{
	return ((t_rgb){
		.r = a.r * b.r,
		.g = a.g * b.g,
		.b = a.b * b.b
	});
}
