/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_rgb.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 14:41:10 by sbos          #+#    #+#                 */
/*   Updated: 2023/02/01 17:37:14 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rt_structs.h"

#include "init/parse/rt_parse.h"
#include "rgb/rt_rgb.h"
#include "utils/rt_utils.h"
#include "vectors/rt_vectors.h"

t_status	rt_parse_rgb(char **line_ptr, t_rgb *rgb)
{
	rt_skip_whitespace(line_ptr);
	if (rt_parse_range_float(line_ptr, &rgb->r, 0, 255) == ERROR)
		return (ERROR);
	if (rt_skip_separator_comma(line_ptr) == ERROR)
		return (ERROR);
	if (rt_parse_range_float(line_ptr, &rgb->g, 0, 255) == ERROR)
		return (ERROR);
	if (rt_skip_separator_comma(line_ptr) == ERROR)
		return (ERROR);
	if (rt_parse_range_float(line_ptr, &rgb->b, 0, 255) == ERROR)
		return (ERROR);
	if (**line_ptr == ',')
		return (rt_print_error(ERROR_UNEXPECTED_COMMA));
	*rgb = rt_scale(*rgb, 1.0f / 255.0f);
	return (OK);
}
