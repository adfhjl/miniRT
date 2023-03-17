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

#include "libft/src/vector/ft_vector.h"

#include "rt_structs.h"

#include <stdio.h>

static void	rt_print_object(t_object object)
{
	rt_try_print_pos(object);
	rt_try_print_ratio(object);
	rt_try_print_normal(object);
	rt_try_print_diameter(object);
	rt_try_print_height(object);
	rt_try_print_rgb(object);
	rt_try_print_fov(object);
}

void	rt_print_scene(t_data *data)
{
	const char	*object_type_strings[] = {
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
		rt_print_object(object);
		printf("\n");
		object_index++;
	}
}
