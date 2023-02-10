/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_normal.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/10 18:29:11 by sbos          #+#    #+#                 */
/*   Updated: 2023/02/10 18:29:11 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "init/parse/rt_parse.h"

t_status	rt_parse_normal(char **line_ptr, t_vector *vector)
{
	if (rt_parse_vector(line_ptr, vector) == ERROR)
		return (ERROR);
	if (vector->x == 0 && vector->y == 0 && vector->z == 0)
		return (rt_print_error(ERROR_INVALID_ZERO_NORMAL));
	return (OK);
}
