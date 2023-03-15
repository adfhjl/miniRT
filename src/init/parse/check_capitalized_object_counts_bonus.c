/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_capitalized_object_counts_bonus.c            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/13 17:02:30 by sbos          #+#    #+#                 */
/*   Updated: 2023/03/13 17:02:30 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft/src/vector/ft_vector.h"

#include "rt_structs.h"

#include "utils/rt_utils.h"

t_status	rt_check_capitalized_object_counts(t_object *objects)
{
	size_t		object_index;
	size_t		ambient_count;
	size_t		camera_count;
	size_t		light_count;
	t_object	*object;

	object_index = 0;
	ambient_count = 0;
	camera_count = 0;
	light_count = 0;
	while (object_index < ft_vector_get_size(objects))
	{
		object = &objects[object_index];
		if (object->type == OBJECT_TYPE_AMBIENT)
			ambient_count++;
		else if (object->type == OBJECT_TYPE_CAMERA)
			camera_count++;
		else if (object->type == OBJECT_TYPE_LIGHT)
			light_count++;
		object_index++;
	}
	if (ambient_count != 1 || camera_count != 1 || light_count == 0)
		return (rt_print_error(ERROR_WRONG_CAPITALIZED_OBJECT_COUNT));
	return (OK);
}
