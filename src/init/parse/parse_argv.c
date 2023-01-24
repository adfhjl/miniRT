/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_argv.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 14:29:50 by sbos          #+#    #+#                 */
/*   Updated: 2023/01/24 14:29:50 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "init/parse/rt_parse.h"

static void	rt_skip_whitespace(char **line_ptr)
{
	while (ft_isspace(**line_ptr))
		(*line_ptr)++;
}

static t_status	rt_parse_object(char *line, t_object *object)
{
	t_parsing_state	state;
	char			*token;

	rt_skip_whitespace(&line);
	token = rt_parse_token(&line);
	if (token == NULL)
		return (ERROR);

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

static t_status	rt_parse_scene_file(int fd, t_data *data)
{
	t_object	object;
	char		*line;

	data->objects = ft_vector_new(sizeof(*data->objects));
	if (data->objects == NULL)
		return (rt_print_error(ERROR_SYSTEM));

	while (true)
	{
		line = get_next_line(fd);
		// TODO: Is there a way to tell whether gnl just reached eof vs. errored?
		if (line == NULL)
			break ;
		ft_bzero(&object, sizeof(object));
		if (rt_parse_object(line, &object) == ERROR)
			return (ERROR);

		// TODO: Not sure if I want to do this here or loop through the objects later,
		// but I need to make sure that any second encountered A/C/L throws an error

		// TODO: Do I need to malloc object before pushing it?
		if (ft_vector_push(&data->objects, &object) == ERROR)
			return (rt_print_error(ERROR_SYSTEM));
	}

	return (OK);
}

t_status	rt_parse_argv(char *argv[], t_data *data)
{
	size_t	len;
	char	*scene_path;
	int		fd;

	data->scene_name = argv[1];
	len = ft_strlen(data->scene_name);
	if (len < 3 || !ft_str_eq(data->scene_name + len - 3, ".rt"))
		return (rt_print_error(ERROR_INVALID_SCENE_NAME));
	scene_path = ft_strjoin_array(
			(char *[]){SCENE_DIRECTORY_PATH, data->scene_name, NULL});
	if (scene_path == NULL)
		return (rt_print_error(ERROR_SYSTEM));
	fd = open(scene_path, O_RDONLY);
	if (fd == SYSTEM_ERROR_STATUS)
		return (rt_print_error(ERROR_CANT_READ_SCENE_FILE));
	if (rt_parse_scene_file(fd, data) == ERROR)
		return (ERROR);
	return (OK);
}
