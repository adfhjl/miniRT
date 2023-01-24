/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_token.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 14:31:44 by sbos          #+#    #+#                 */
/*   Updated: 2023/01/24 14:31:44 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	rt_skip_non_whitespace(char **line_ptr)
{
	while (!ft_isspace(**line_ptr))
		(*line_ptr)++;
}

char	*rt_parse_token(char **line_ptr)
{
	char	*start;
	char	*end;
	size_t	token_len;
	char	*token;

	start = *line_ptr;
	rt_skip_non_whitespace(line_ptr);
	end = *line_ptr;
	token_len = (size_t)(end - start);
	token = ft_substr(*line_ptr - token_len, 0, token_len);
	if (token == NULL)
		rt_print_error(ERROR_SYSTEM);
	return (token);
}
