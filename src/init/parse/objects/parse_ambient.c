/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_ambient.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 15:38:52 by sbos          #+#    #+#                 */
/*   Updated: 2023/01/24 15:38:52 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "init/parse/rt_parse.h"

t_status	rt_parse_ambient(char **line_ptr, t_object *object)
{
	if (rt_parse_range_float(line_ptr, &object->ambient.ratio, 0, 1) == ERROR)
		return (ERROR);
	if (rt_parse_rgb(line_ptr, &object->ambient.rgb) == ERROR)
		return (ERROR);
	return (OK);
}
