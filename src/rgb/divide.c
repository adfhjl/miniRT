/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   divide.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbenneko <vbenneko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/01 16:23:04 by vbenneko      #+#    #+#                 */
/*   Updated: 2023/02/01 17:16:45 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rt_structs.h"

t_rgb	rt_divide_rgb(t_rgb a, t_rgb b)
{
	return ((t_rgb){
		a.r / b.r,
		a.g / b.g,
		a.b / b.b
	});
}
