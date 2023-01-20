/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug_print_objects.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/20 17:07:24 by sbos          #+#    #+#                 */
/*   Updated: 2023/01/20 17:07:24 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "debug/rt_debug.h"

#include <stdio.h>

// TODO: Comment out this file before handing it in

void	rt_debug_print_line(void)
{
	// printf("+-OBJECT_TYPE_CYLINDER-+-1.2---+-255,255,255-+-1.2,3.4,5.6-+-1.2,3.4,5.6-+-255-+-1.2--------+-1.2,3.4,5.6-+-1.2------+-1.2----+\n");
	   printf("+----------------------+-------+-------------+-------------+-------------+-----+------------+-------------+----------+--------+\n");
}

void	rt_debug_print_objects(t_data *data)
{
	char	*object_type_strings[] = {
		[OBJECT_TYPE_NONE] = "OBJECT_TYPE_NONE",
		[OBJECT_TYPE_AMBIENT] = "OBJECT_TYPE_AMBIENT",
		[OBJECT_TYPE_CAMERA] = "OBJECT_TYPE_CAMERA",
		[OBJECT_TYPE_LIGHT] = "OBJECT_TYPE_LIGHT",
		[OBJECT_TYPE_SPHERE] = "OBJECT_TYPE_SPHERE",
		[OBJECT_TYPE_PLANE] = "OBJECT_TYPE_PLANE",
		[OBJECT_TYPE_CYLINDER] = "OBJECT_TYPE_CYLINDER",
	};
	size_t		i;
	size_t		size;
	t_object	*object;

	rt_debug_print_line();
	printf("| object type          | ratio | rgb         | coordinates | orientation | fov | brightness | center      | diameter | height |\n");
	rt_debug_print_line();

	i = 0;
	size = ft_vector_get_size(data->objects);
	while (i < size)
	{
		object = &data->objects[i];

		printf("|");

		printf(" %-20s |", object_type_strings[object->type]);

		if (object->type == OBJECT_TYPE_AMBIENT)
			printf(" %.1f   |", object->ambient.ratio);
		else
			printf("       |");

		if (object->type == OBJECT_TYPE_AMBIENT)
			printf(" %d,%d,%d |", object->ambient.rgb.r, object->ambient.rgb.g, object->ambient.rgb.b);
		else if (object->type == OBJECT_TYPE_SPHERE)
			printf(" %d,%d,%d |", object->sphere.rgb.r, object->sphere.rgb.g, object->sphere.rgb.b);
		else if (object->type == OBJECT_TYPE_PLANE)
			printf(" %d,%d,%d |", object->plane.rgb.r, object->plane.rgb.g, object->plane.rgb.b);
		else if (object->type == OBJECT_TYPE_CYLINDER)
			printf(" %d,%d,%d |", object->cylinder.rgb.r, object->cylinder.rgb.g, object->cylinder.rgb.b);
		else
			printf("             |");

		if (object->type == OBJECT_TYPE_CAMERA)
			printf(" %.1f,%.1f,%.1f |", object->camera.coordinates.x, object->camera.coordinates.y, object->camera.coordinates.z);
		else if (object->type == OBJECT_TYPE_LIGHT)
			printf(" %.1f,%.1f,%.1f |", object->light.coordinates.x, object->light.coordinates.y, object->light.coordinates.z);
		else if (object->type == OBJECT_TYPE_PLANE)
			printf(" %.1f,%.1f,%.1f |", object->plane.coordinates.x, object->plane.coordinates.y, object->plane.coordinates.z);
		else if (object->type == OBJECT_TYPE_CYLINDER)
			printf(" %.1f,%.1f,%.1f |", object->cylinder.coordinates.x, object->cylinder.coordinates.y, object->cylinder.coordinates.z);
		else
			printf("             |");

		if (object->type == OBJECT_TYPE_CAMERA)
			printf(" %.1f,%.1f,%.1f |", object->camera.orientation.x, object->camera.orientation.y, object->camera.orientation.z);
		if (object->type == OBJECT_TYPE_PLANE)
			printf(" %.1f,%.1f,%.1f |", object->plane.orientation.x, object->plane.orientation.y, object->plane.orientation.z);
		if (object->type == OBJECT_TYPE_CYLINDER)
			printf(" %.1f,%.1f,%.1f |", object->cylinder.orientation.x, object->cylinder.orientation.y, object->cylinder.orientation.z);
		else
			printf("             |");

		if (object->type == OBJECT_TYPE_CAMERA)
			printf(" %d |", object->camera.fov);
		else
			printf("     |");

		if (object->type == OBJECT_TYPE_LIGHT)
			printf(" %.1f |", object->light.brightness);
		else
			printf("            |");

		if (object->type == OBJECT_TYPE_SPHERE)
			printf(" %.1f,%.1f,%.1f |", object->sphere.center.x, object->sphere.center.y, object->sphere.center.z);
		else
			printf("             |");

		if (object->type == OBJECT_TYPE_SPHERE)
			printf(" %.1f |", object->sphere.diameter);
		else if (object->type == OBJECT_TYPE_CYLINDER)
			printf(" %.1f |", object->cylinder.diameter);
		else
			printf("          |");

		if (object->type == OBJECT_TYPE_CYLINDER)
			printf(" %.1f |", object->cylinder.height);
		else
			printf("        |");

		printf("\n");
		rt_debug_print_line();

		i++;
	}
}
