/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_char.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 14:38:23 by sbos          #+#    #+#                 */
/*   Updated: 2023/01/24 14:38:23 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_status	rt_get_nbr_token(char **token_ptr, char **nbr_token_destination)
{
	char	*start;
	char	*end;
	size_t	token_len;
	char	*nbr_token;

	start = *token_ptr;
	end = ft_str_not_set(start, DIGITS);
	if (end == NULL)
		token_len = ft_strlen(start);
	else
		token_len = (size_t)(end - start);
	nbr_token = ft_substr(*token_ptr, 0, token_len);
	if (nbr_token == NULL)
		rt_print_error(ERROR_SYSTEM);
	*nbr_token_destination = nbr_token;
	if (end == NULL)
		**token_ptr = '\0';
	else
		*token_ptr = end;
	return (OK);
}

t_status	rt_parse_char(char **token_ptr, unsigned char *field_ptr)
{
	char	*nbr_token;
	int		nbr;

	if (rt_get_nbr_token(token_ptr, &nbr_token) == ERROR)
		return (ERROR);
	if (!ft_atoi_safe(nbr_token, &nbr) || nbr < 0 || nbr > 255)
		return (rt_print_error(ERROR_FAILED_TO_PARSE_CHAR));
	*field_ptr = (unsigned char)nbr;
	return (OK);
}
