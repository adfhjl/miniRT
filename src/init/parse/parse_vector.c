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

#include "minirt.h"
#include "init/parse/rt_parse.h"

t_status	rt_parse_vector(char *token, t_vector *vector)
{
	if (*token == ',')
		return (rt_print_error(ERROR_UNEXPECTED_COMMA));
	if (rt_parse_float(&token, &vector->x) == ERROR)
		return (ERROR);
	if (rt_skip_separator_comma(&token) == ERROR)
		return (ERROR);
	if (rt_parse_float(&token, &vector->y) == ERROR)
		return (ERROR);
	if (rt_skip_separator_comma(&token) == ERROR)
		return (ERROR);
	if (rt_parse_float(&token, &vector->z) == ERROR)
		return (ERROR);
	if (*token == ',')
		return (rt_print_error(ERROR_UNEXPECTED_COMMA));
	return (OK);
}
