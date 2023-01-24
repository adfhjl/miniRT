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
#include "init/parse/objects/rt_parse_objects.h"

static t_status	rt_set_object_type(char *token, t_object *object)
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

static void	rt_skip_non_whitespace(char **line_ptr)
{
	while (!ft_isspace(**line_ptr))
		(*line_ptr)++;
}

static char	*rt_parse_object_type(char **line_ptr)
{
	char	*start;
	char	*end;
	size_t	token_len;
	char	*token;

	rt_skip_whitespace(line_ptr);
	start = *line_ptr;
	rt_skip_non_whitespace(line_ptr);
	end = *line_ptr;
	token_len = (size_t)(end - start);
	token = ft_substr(*line_ptr - token_len, 0, token_len);
	if (token == NULL)
		rt_print_error(ERROR_SYSTEM);
	return (token);
}

t_status	rt_parse_object(char *line, t_object *object)
{
	char				*object_type_token;
	const t_parse_fn	parse_fns[] = {
	[OBJECT_TYPE_AMBIENT] = rt_parse_ambient,
	[OBJECT_TYPE_CAMERA] = rt_parse_camera,
	[OBJECT_TYPE_LIGHT] = rt_parse_light,
	[OBJECT_TYPE_SPHERE] = rt_parse_sphere,
	[OBJECT_TYPE_PLANE] = rt_parse_plane,
	[OBJECT_TYPE_CYLINDER] = rt_parse_cylinder,
	};

	object_type_token = rt_parse_object_type(&line);
	if (object_type_token == NULL)
		return (ERROR);
	if (rt_set_object_type(object_type_token, object) == ERROR)
		return (ERROR);
	if (parse_fns[object->type](&line, object) == ERROR)
		return (ERROR);
	rt_skip_whitespace(&line);
	if (*line != '\0')
		return (rt_print_error(ERROR_UNEXPECTED_EXTRA_FIELD));
	return (OK);
}
