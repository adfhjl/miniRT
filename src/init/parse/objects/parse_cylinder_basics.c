/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_cylinder_basics.c                            :+:    :+:            */
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

#include "utils/rt_utils.h"

t_status	rt_parse_cylinder_basics(char **line_ptr, t_object *cylinder)
{
	if (rt_parse_vector(line_ptr, &cylinder->pos) == ERROR
		|| rt_check_separating_whitespace(line_ptr) == ERROR
		|| rt_parse_normal(line_ptr, &cylinder->normal) == ERROR
		|| rt_check_separating_whitespace(line_ptr) == ERROR
		|| rt_parse_float(line_ptr, &cylinder->diameter) == ERROR
		|| rt_check_separating_whitespace(line_ptr) == ERROR
		|| rt_parse_float(line_ptr, &cylinder->height) == ERROR
		|| rt_check_separating_whitespace(line_ptr) == ERROR
		|| rt_parse_rgb(line_ptr, &cylinder->material.rgb) == ERROR)
		return (ERROR);
	if (cylinder->diameter <= 0 || cylinder->height <= 0)
		return (rt_print_error(ERROR_FLOAT_OUT_OF_RANGE));
	return (OK);
}
