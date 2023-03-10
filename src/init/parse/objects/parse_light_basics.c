/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_light_basics.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/10 20:28:04 by sbos          #+#    #+#                 */
/*   Updated: 2023/03/10 20:28:04 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rt_structs.h"

#include "init/parse/objects/rt_parse_objects.h"
#include "init/parse/rt_parse.h"

t_status	rt_parse_light_basics(char **line_ptr, t_object *light)
{
	if (rt_parse_vector(line_ptr, &light->pos) == ERROR
		|| rt_check_separating_whitespace(line_ptr) == ERROR
		|| rt_parse_range_float(line_ptr, &light->ratio, 0, 1) == ERROR
		|| rt_check_separating_whitespace(line_ptr) == ERROR
		|| rt_parse_rgb(line_ptr, &light->material.rgb) == ERROR)
		return (ERROR);
	return (OK);
}
