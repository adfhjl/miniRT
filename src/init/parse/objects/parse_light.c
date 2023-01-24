/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_light.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 15:40:10 by sbos          #+#    #+#                 */
/*   Updated: 2023/01/24 15:40:10 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "init/parse/rt_parse.h"

t_status	rt_parse_light(char **line_ptr, t_object *object)
{
	if (rt_parse_vector(line_ptr, &object->light.coordinates) == ERROR)
		return (ERROR);
	if (rt_parse_range_float(line_ptr, &object->light.brightness,
			0, 1) == ERROR)
		return (ERROR);
	return (OK);
}
