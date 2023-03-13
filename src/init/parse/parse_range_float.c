/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_range_float.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 16:48:46 by sbos          #+#    #+#                 */
/*   Updated: 2023/01/24 16:48:46 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft/src/error/ft_error.h"

#include "rt_enums.h"
#include "rt_typedefs.h"

#include "init/parse/rt_parse.h"
#include "utils/rt_utils.h"

t_status	rt_parse_range_float(char **line_ptr, float *field_ptr,
				float start, float end)
{
	if (rt_parse_float(line_ptr, field_ptr) == ERROR)
		return (ERROR);
	if (*field_ptr < start || *field_ptr > end)
		return (rt_print_error(ERROR_FLOAT_OUT_OF_RANGE));
	return (OK);
}
