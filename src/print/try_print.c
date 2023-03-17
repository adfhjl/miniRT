/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   try_print.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 19:07:16 by sbos          #+#    #+#                 */
/*   Updated: 2023/03/17 19:07:16 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rt_structs.h"

#include "print/rt_print.h"

#include <stdio.h>

void	rt_try_print_rgb(t_object object)
{
	if (object.type == OBJECT_TYPE_AMBIENT
		|| object.type == OBJECT_TYPE_LIGHT
		|| object.type == OBJECT_TYPE_SPHERE
		|| object.type == OBJECT_TYPE_PLANE
		|| object.type == OBJECT_TYPE_CYLINDER)
		rt_print_rgb(object.material.rgb);
}

void	rt_try_print_diameter(t_object object)
{
	if (object.type == OBJECT_TYPE_SPHERE
		|| object.type == OBJECT_TYPE_CYLINDER)
		printf(" %.2f", object.diameter);
}

void	rt_try_print_normal(t_object object)
{
	if (object.type == OBJECT_TYPE_CAMERA
		|| object.type == OBJECT_TYPE_PLANE
		|| object.type == OBJECT_TYPE_CYLINDER)
		rt_print_vector(object.normal);
}

void	rt_try_print_ratio(t_object object)
{
	if (object.type == OBJECT_TYPE_AMBIENT
		|| object.type == OBJECT_TYPE_LIGHT)
		printf(" %.2f", object.ratio);
}

void	rt_try_print_pos(t_object object)
{
	if (object.type == OBJECT_TYPE_CAMERA
		|| object.type == OBJECT_TYPE_LIGHT
		|| object.type == OBJECT_TYPE_SPHERE
		|| object.type == OBJECT_TYPE_PLANE
		|| object.type == OBJECT_TYPE_CYLINDER)
		rt_print_vector(object.pos);
}
