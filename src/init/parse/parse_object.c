/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_object.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 15:07:13 by sbos          #+#    #+#                 */
/*   Updated: 2023/01/24 15:07:13 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "init/parse/rt_parse.h"

static t_status	rt_init_object_type(char *token, t_object *object)
{
	if (ft_str_eq(token, "A"))
		object->type = OBJECT_TYPE_AMBIENT;
	else if (ft_str_eq(token, "C"))
		object->type = OBJECT_TYPE_CAMERA;
	else if (ft_str_eq(token, "L"))
		object->type = OBJECT_TYPE_LIGHT;
	else if (ft_str_eq(token, "sp"))
		object->type = OBJECT_TYPE_SPHERE;
	else if (ft_str_eq(token, "pl"))
		object->type = OBJECT_TYPE_PLANE;
	else if (ft_str_eq(token, "cy"))
		object->type = OBJECT_TYPE_CYLINDER;
	else
		return (rt_print_error(ERROR_NON_OBJECT_TYPE_START));
	return (OK);
}

static void	rt_skip_whitespace(char **line_ptr)
{
	while (ft_isspace(**line_ptr))
		(*line_ptr)++;
}

t_status	rt_parse_object(char *line, t_object *object)
{
	t_parsing_state	state;
	char			*token;

	rt_skip_whitespace(&line);
	token = rt_parse_token(&line);
	if (token == NULL)
		return (ERROR);
	if (rt_init_object_type(token, object) == ERROR)
		return (ERROR);
	state = PARSING_STATE_TYPE;
	while (true)
	{
		rt_skip_whitespace(&line);
		if (*line == '\0')
			break ;
		token = rt_parse_token(&line);
		if (token == NULL)
			return (ERROR);
		if (state == PARSING_STATE_END)
			return (rt_print_error(ERROR_UNEXPECTED_EXTRA_FIELD));
		if (rt_parse_field(token, object, &state) == ERROR)
			return (ERROR);
	}
	return (OK);
}
