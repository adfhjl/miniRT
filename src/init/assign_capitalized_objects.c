/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   assign_capitalized_objects.c                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 18:11:40 by sbos          #+#    #+#                 */
/*   Updated: 2023/03/17 18:11:40 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft/src/vector/ft_vector.h"

#include "rt_structs.h"

static t_object	*rt_get_object_ptr(t_object_type searched_object_type,
					t_object *objects)
{
	size_t	object_index;
	size_t	size;

	object_index = 0;
	size = ft_vector_get_size(objects);
	while (object_index < size)
	{
		if (objects[object_index].type == searched_object_type)
			return (&objects[object_index]);
		object_index++;
	}
	return (NULL);
}

void	rt_assign_capitalized_objects(t_data *data)
{
	data->ambient = rt_get_object_ptr(OBJECT_TYPE_AMBIENT, data->objects);
	data->camera = rt_get_object_ptr(OBJECT_TYPE_CAMERA, data->objects);
}
