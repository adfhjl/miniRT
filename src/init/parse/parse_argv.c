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

static bool	rt_seen_capitalized_object_before(t_object_type object_type,
				bool seen_ambient, bool seen_camera, bool seen_light)
{
	return ((object_type == OBJECT_TYPE_AMBIENT && seen_ambient)
		|| (object_type == OBJECT_TYPE_CAMERA && seen_camera)
		|| (object_type == OBJECT_TYPE_LIGHT && seen_light));
}

static bool	rt_has_duplicate_capitalized_object(t_object *objects)
{
	size_t		object_index;
	bool		seen_ambient;
	bool		seen_camera;
	bool		seen_light;
	t_object	*object;

	object_index = 0;
	seen_ambient = false;
	seen_camera = false;
	seen_light = false;
	while (object_index < ft_vector_get_size(objects))
	{
		object = &objects[object_index];
		if (rt_seen_capitalized_object_before(object->type, seen_ambient,
				seen_camera, seen_light))
			return (true);
		if (object->type == OBJECT_TYPE_AMBIENT)
			seen_ambient = true;
		if (object->type == OBJECT_TYPE_CAMERA)
			seen_camera = true;
		if (object->type == OBJECT_TYPE_LIGHT)
			seen_light = true;
		object_index++;
	}
	return (false);
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
	if (rt_has_duplicate_capitalized_object(data->objects))
		return (rt_print_error(ERROR_DUPLICATE_CAPITALIZED_OBJECT));
	return (OK);
}
