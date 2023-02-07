/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug_print_objects.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/20 17:07:24 by sbos          #+#    #+#                 */
/*   Updated: 2023/02/01 17:34:41 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "debug/rt_debug.h"

#include <stdio.h>

// TODO: Comment out this file before handing it in

#define EMPTY_FIELD_STRING ""

void	rt_debug_print_field_value(char *field_name, char *field_value)
{
	size_t	field_name_len;
	size_t	field_len;

	field_name_len = ft_strlen(field_name);
	if (field_value)
		field_len = ft_max_size(field_name_len, ft_strlen(field_value));
	else
		field_len = ft_max_size(field_name_len, ft_strlen(EMPTY_FIELD_STRING));
	if (field_value == NULL)
		field_value = EMPTY_FIELD_STRING;
	printf(" %-*s |", (int)field_len, field_value);
}

void	rt_debug_print_field_name(char *field_name, char *field_value)
{
	size_t	field_name_len;
	size_t	field_len;
	char	*field_name_line;

	field_name_len = ft_strlen(field_name);
	if (field_value)
		field_len = ft_max_size(field_name_len, ft_strlen(field_value));
	else
		field_len = ft_max_size(field_name_len, ft_strlen(EMPTY_FIELD_STRING));
	field_name_line = ft_stralloc(field_len);
	ft_strlcpy(field_name_line, field_name, field_len + 1);
	ft_memset(field_name_line + field_name_len, '-', field_len - field_name_len);
	printf("-%s-v", field_name_line);
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
	size_t		object_index;
	size_t		size;
	t_object	*object;

	object_index = 0;
	size = ft_vector_get_size(data->objects);
	while (object_index < size)
	{
		object = &data->objects[object_index];

		char	*object_type = NULL;
		asprintf(&object_type, "%-20s", object_type_strings[object->type]);

		char	*ratio = NULL;
		if (object->type == OBJECT_TYPE_AMBIENT)
			asprintf(&ratio, "%.1f", object->ambient.ratio);

		char	*rgb = NULL;
		if (object->type == OBJECT_TYPE_AMBIENT)
			asprintf(&rgb, "%.0f,%.0f,%.0f", object->ambient.rgb.r, object->ambient.rgb.g, object->ambient.rgb.b);
		else if (object->type == OBJECT_TYPE_SPHERE)
			asprintf(&rgb, "%.0f,%.0f,%.0f", object->sphere.rgb.r, object->sphere.rgb.g, object->sphere.rgb.b);
		else if (object->type == OBJECT_TYPE_PLANE)
			asprintf(&rgb, "%.0f,%.0f,%.0f", object->plane.rgb.r, object->plane.rgb.g, object->plane.rgb.b);
		else if (object->type == OBJECT_TYPE_CYLINDER)
			asprintf(&rgb, "%.0f,%.0f,%.0f", object->cylinder.rgb.r, object->cylinder.rgb.g, object->cylinder.rgb.b);

		char	*coordinates = NULL;
		if (object->type == OBJECT_TYPE_CAMERA)
			asprintf(&coordinates, "%.1f,%.1f,%.1f", object->camera.coordinates.x, object->camera.coordinates.y, object->camera.coordinates.z);
		else if (object->type == OBJECT_TYPE_LIGHT)
			asprintf(&coordinates, "%.1f,%.1f,%.1f", object->light.coordinates.x, object->light.coordinates.y, object->light.coordinates.z);
		else if (object->type == OBJECT_TYPE_PLANE)
			asprintf(&coordinates, "%.1f,%.1f,%.1f", object->plane.coordinates.x, object->plane.coordinates.y, object->plane.coordinates.z);
		else if (object->type == OBJECT_TYPE_CYLINDER)
			asprintf(&coordinates, "%.1f,%.1f,%.1f", object->cylinder.coordinates.x, object->cylinder.coordinates.y, object->cylinder.coordinates.z);

		char	*orientation = NULL;
		if (object->type == OBJECT_TYPE_CAMERA)
			asprintf(&orientation, "%.1f,%.1f,%.1f", object->camera.orientation.x, object->camera.orientation.y, object->camera.orientation.z);
		if (object->type == OBJECT_TYPE_PLANE)
			asprintf(&orientation, "%.1f,%.1f,%.1f", object->plane.orientation.x, object->plane.orientation.y, object->plane.orientation.z);
		if (object->type == OBJECT_TYPE_CYLINDER)
			asprintf(&orientation, "%.1f,%.1f,%.1f", object->cylinder.orientation.x, object->cylinder.orientation.y, object->cylinder.orientation.z);

		char	*fov = NULL;
		if (object->type == OBJECT_TYPE_CAMERA)
			asprintf(&fov, "%.1f", object->camera.fov);

		char	*brightness = NULL;
		if (object->type == OBJECT_TYPE_LIGHT)
			asprintf(&brightness, "%.1f", object->light.brightness);

		char	*center = NULL;
		if (object->type == OBJECT_TYPE_SPHERE)
			asprintf(&center, "%.1f,%.1f,%.1f", object->sphere.center.x, object->sphere.center.y, object->sphere.center.z);

		char	*diameter = NULL;
		if (object->type == OBJECT_TYPE_SPHERE)
			asprintf(&diameter, "%.1f", object->sphere.diameter);
		else if (object->type == OBJECT_TYPE_CYLINDER)
			asprintf(&diameter, "%.1f", object->cylinder.diameter);

		char	*height = NULL;
		if (object->type == OBJECT_TYPE_CYLINDER)
			asprintf(&height, "%.1f", object->cylinder.height);

		printf("|");
		rt_debug_print_field_name("object type", object_type);
		rt_debug_print_field_name("ratio", ratio);
		rt_debug_print_field_name("rgb", rgb);
		rt_debug_print_field_name("coordinates", coordinates);
		rt_debug_print_field_name("orientation", orientation);
		rt_debug_print_field_name("fov", fov);
		rt_debug_print_field_name("brightness", brightness);
		rt_debug_print_field_name("center", center);
		rt_debug_print_field_name("diameter", diameter);
		rt_debug_print_field_name("height", height);
		printf("\n");

		printf("|");
		rt_debug_print_field_value("object type", object_type);
		rt_debug_print_field_value("ratio", ratio);
		rt_debug_print_field_value("rgb", rgb);
		rt_debug_print_field_value("coordinates", coordinates);
		rt_debug_print_field_value("orientation", orientation);
		rt_debug_print_field_value("fov", fov);
		rt_debug_print_field_value("brightness", brightness);
		rt_debug_print_field_value("center", center);
		rt_debug_print_field_value("diameter", diameter);
		rt_debug_print_field_value("height", height);
		printf("\n");

		object_index++;
	}
}
