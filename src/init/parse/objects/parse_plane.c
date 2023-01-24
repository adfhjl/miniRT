/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_plane.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 15:40:10 by sbos          #+#    #+#                 */
/*   Updated: 2023/01/24 15:40:10 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "init/parse/rt_parse.h"

t_status	rt_parse_plane(char **line_ptr, t_object *object)
{
	if (rt_parse_vector(line_ptr, &object->plane.coordinates) == ERROR)
		return (ERROR);
	if (rt_parse_vector(line_ptr, &object->plane.orientation) == ERROR)
		return (ERROR);
	if (rt_parse_rgb(line_ptr, &object->plane.rgb) == ERROR)
		return (ERROR);
	return (OK);
}
