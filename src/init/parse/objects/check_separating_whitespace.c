/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_separating_whitespace.c                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 17:35:56 by sbos          #+#    #+#                 */
/*   Updated: 2023/01/24 17:35:56 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft/src/helper_headers/ft_defines.h"
#include "libft/src/str/ft_str.h"

#include "utils/rt_utils.h"

t_status	rt_check_separating_whitespace(char **line_ptr)
{
	if (!ft_chr_in_str(**line_ptr, WHITESPACE))
		return (rt_print_error(ERROR_EXPECTED_WHITESPACE));
	return (OK);
}
