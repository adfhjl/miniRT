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

		if (object.type == OBJECT_TYPE_CAMERA
		|| object.type == OBJECT_TYPE_LIGHT
		|| object.type == OBJECT_TYPE_SPHERE
		|| object.type == OBJECT_TYPE_PLANE
		|| object.type == OBJECT_TYPE_CYLINDER)
			printf(" %.1f,%.1f,%.1f", object.pos.x, object.pos.y, object.pos.z);

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

		if (object.type == OBJECT_TYPE_AMBIENT
		|| object.type == OBJECT_TYPE_LIGHT
		|| object.type == OBJECT_TYPE_SPHERE
		|| object.type == OBJECT_TYPE_PLANE
		|| object.type == OBJECT_TYPE_CYLINDER)
			rt_print_rgb(object.rgb);

		if (object.type == OBJECT_TYPE_CAMERA)
			printf(" %.1f", object.fov);

		printf("\n");

		object_index++;
	}
}
