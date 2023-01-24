/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   skip_separator_comma.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 14:42:14 by sbos          #+#    #+#                 */
/*   Updated: 2023/01/24 14:42:14 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_status	rt_skip_separator_comma(char **line_ptr)
{
	if (**line_ptr != ',')
		return (rt_print_error(ERROR_EXPECTED_COMMA));
	(*line_ptr)++;
	return (OK);
}
