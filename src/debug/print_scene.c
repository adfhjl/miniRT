/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_scene.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/20 17:07:24 by sbos          #+#    #+#                 */
/*   Updated: 2023/02/01 17:34:41 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#include <stdio.h>

static void	rt_print_rgb(t_rgb rgb)
{
	int	r;
	int	g;
	int	b;

	r = (int)(rgb.r * 255);
	g = (int)(rgb.g * 255);
	b = (int)(rgb.b * 255);
	printf(" %i,%i,%i", r, g, b);
}

static void	rt_print_object_rgb(t_object object)
{
	if (object.type == OBJECT_TYPE_AMBIENT)
		rt_print_rgb(object.rgb);
	else if (object.type == OBJECT_TYPE_LIGHT)
		rt_print_rgb(object.rgb);
	else if (object.type == OBJECT_TYPE_SPHERE)
		rt_print_rgb(object.rgb);
	else if (object.type == OBJECT_TYPE_PLANE)
		rt_print_rgb(object.rgb);
	else if (object.type == OBJECT_TYPE_CYLINDER)
		rt_print_rgb(object.rgb);
}

static void	rt_print_object_origin(t_object object)
{
	if (object.type == OBJECT_TYPE_CAMERA)
		printf(" %.1f,%.1f,%.1f", object.origin.x, object.origin.y, object.origin.z);
	else if (object.type == OBJECT_TYPE_LIGHT)
		printf(" %.1f,%.1f,%.1f", object.origin.x, object.origin.y, object.origin.z);
	else if (object.type == OBJECT_TYPE_SPHERE)
		printf(" %.1f,%.1f,%.1f", object.origin.x, object.origin.y, object.origin.z);
	else if (object.type == OBJECT_TYPE_PLANE)
		printf(" %.1f,%.1f,%.1f", object.origin.x, object.origin.y, object.origin.z);
	else if (object.type == OBJECT_TYPE_CYLINDER)
		printf(" %.1f,%.1f,%.1f", object.origin.x, object.origin.y, object.origin.z);
}

void	rt_print_scene(t_data *data)
{
	char	*object_type_strings[] = {
		[OBJECT_TYPE_AMBIENT] = "A",
		[OBJECT_TYPE_CAMERA] = "C",
		[OBJECT_TYPE_LIGHT] = "L",
		[OBJECT_TYPE_SPHERE] = "sp",
		[OBJECT_TYPE_PLANE] = "pl",
		[OBJECT_TYPE_CYLINDER] = "cy",
	};
	size_t		object_index;
	size_t		size;
	t_object	object;

	object_index = 0;
	size = ft_vector_get_size(data->objects);
	while (object_index < size)
	{
		object = data->objects[object_index];

		printf("%s", object_type_strings[object.type]);

		rt_print_object_origin(object);

		if (object.type == OBJECT_TYPE_AMBIENT
		|| object.type == OBJECT_TYPE_LIGHT)
			printf(" %.1f", object.ratio);

		if (object.type == OBJECT_TYPE_CAMERA
		|| object.type == OBJECT_TYPE_PLANE
		|| object.type == OBJECT_TYPE_CYLINDER)
			printf(" %.1f,%.1f,%.1f", object.normal.x, object.normal.y, object.normal.z);

		if (object.type == OBJECT_TYPE_SPHERE
		|| object.type == OBJECT_TYPE_CYLINDER)
			printf(" %.1f", object.diameter);

		if (object.type == OBJECT_TYPE_CYLINDER)
			printf(" %.1f", object.height);

		rt_print_object_rgb(object);

		if (object.type == OBJECT_TYPE_CAMERA)
			printf(" %.1f", object.fov);

		printf("\n");

		object_index++;
	}
}
