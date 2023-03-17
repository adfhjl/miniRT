/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_plane_bonus.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 15:40:10 by sbos          #+#    #+#                 */
/*   Updated: 2023/01/24 15:40:10 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rt_structs.h"

#include "init/parse/objects/rt_parse_objects.h"

t_status	rt_parse_plane(char **line_ptr, t_object *plane)
{
	if (rt_parse_plane_basics(line_ptr, plane) == ERROR
		|| rt_parse_material(line_ptr, &plane->material) == ERROR)
		return (ERROR);
	return (OK);
}
