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

#include "libft/src/error/ft_error.h"

#include "rt_enums.h"
#include "rt_typedefs.h"

#include "utils/rt_utils.h"

t_status	rt_skip_separator_comma(char **line_ptr)
{
	if (**line_ptr != ',')
		return (rt_print_error(ERROR_EXPECTED_COMMA));
	(*line_ptr)++;
	return (OK);
}
