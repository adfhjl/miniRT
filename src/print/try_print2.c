/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   try_print2.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 19:11:00 by sbos          #+#    #+#                 */
/*   Updated: 2023/03/17 19:11:00 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rt_structs.h"

#include <stdio.h>

void	rt_try_print_height(t_object object)
{
	if (object.type == OBJECT_TYPE_CYLINDER)
		printf(" %.2f", object.height);
}

void	rt_try_print_fov(t_object object)
{
	if (object.type == OBJECT_TYPE_CAMERA)
		printf(" %.2f", object.fov);
}
