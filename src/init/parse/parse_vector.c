/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_vector.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 14:41:23 by sbos          #+#    #+#                 */
/*   Updated: 2023/01/24 14:41:23 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rt_structs.h"

#include "init/parse/rt_parse.h"
#include "utils/rt_utils.h"

t_status	rt_parse_vector(char **line_ptr, t_vector *vector)
{
	rt_skip_whitespace(line_ptr);
	if (rt_parse_float(line_ptr, &vector->x) == ERROR)
		return (ERROR);
	if (rt_skip_separator_comma(line_ptr) == ERROR)
		return (ERROR);
	if (rt_parse_float(line_ptr, &vector->y) == ERROR)
		return (ERROR);
	if (rt_skip_separator_comma(line_ptr) == ERROR)
		return (ERROR);
	if (rt_parse_float(line_ptr, &vector->z) == ERROR)
		return (ERROR);
	if (**line_ptr == ',')
		return (rt_print_error(ERROR_UNEXPECTED_COMMA));
	return (OK);
}
