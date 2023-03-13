/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   has_duplicate_object.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/13 17:01:25 by sbos          #+#    #+#                 */
/*   Updated: 2023/03/13 17:01:25 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	rt_has_duplicate_capitalized_object(t_object *objects)
{
	size_t		object_index;
	bool		seen_ambient;
	bool		seen_camera;
	bool		seen_light;
	t_object	*object;

	object_index = 0;
	seen_ambient = false;
	seen_camera = false;
	seen_light = false;
	while (object_index < ft_vector_get_size(objects))
	{
		object = &objects[object_index];
		if ((object->type == OBJECT_TYPE_AMBIENT && seen_ambient)
			|| (object->type == OBJECT_TYPE_CAMERA && seen_camera)
			|| (object->type == OBJECT_TYPE_LIGHT && seen_light))
			return (true);
		if (object->type == OBJECT_TYPE_AMBIENT)
			seen_ambient = true;
		if (object->type == OBJECT_TYPE_CAMERA)
			seen_camera = true;
		if (object->type == OBJECT_TYPE_LIGHT)
			seen_light = true;
		object_index++;
	}
	return (false);
}
