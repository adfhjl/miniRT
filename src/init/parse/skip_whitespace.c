/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   skip_whitespace.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 16:10:09 by sbos          #+#    #+#                 */
/*   Updated: 2023/01/24 16:10:09 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft/src/char/ft_char.h"

void	rt_skip_whitespace(char **line_ptr)
{
	while (ft_isspace(**line_ptr))
		(*line_ptr)++;
}
