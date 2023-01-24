/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_rgb.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 14:41:10 by sbos          #+#    #+#                 */
/*   Updated: 2023/01/24 14:41:10 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "init/parse/rt_parse.h"

t_status	rt_parse_rgb(char *token, t_rgb *rgb)
{
	if (*token == ',')
		return (rt_print_error(ERROR_UNEXPECTED_COMMA));
	if (rt_parse_char(&token, &rgb->r) == ERROR)
		return (ERROR);
	if (rt_skip_separator_comma(&token) == ERROR)
		return (ERROR);
	if (rt_parse_char(&token, &rgb->g) == ERROR)
		return (ERROR);
	if (rt_skip_separator_comma(&token) == ERROR)
		return (ERROR);
	if (rt_parse_char(&token, &rgb->b) == ERROR)
		return (ERROR);
	if (*token == ',')
		return (rt_print_error(ERROR_UNEXPECTED_COMMA));
	return (OK);
}
