/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_float.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 14:35:51 by sbos          #+#    #+#                 */
/*   Updated: 2023/01/24 14:35:51 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_status	rt_parse_float(char **line_ptr, float *field_ptr)
{
	char	*end;

	*field_ptr = ft_strtof(*line_ptr, &end);
	if (*line_ptr == end)
		return (rt_print_error(ERROR_FAILED_TO_PARSE_FLOAT));
	(*line_ptr) = end;
	return (OK);
}