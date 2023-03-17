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

#include "libft/src/gnl/get_next_line.h"
#include "libft/src/mem/ft_mem.h"
#include "libft/src/str/ft_str.h"
#include "libft/src/vector/ft_vector.h"

#include "rt_structs.h"

#include "init/parse/rt_parse.h"
#include "utils/rt_utils.h"

#include <fcntl.h>
#include <unistd.h>

static t_status	rt_parse_scene_file(int fd, t_data *data)
{
	t_object	object;
	char		*line;

	data->objects = ft_vector_new(sizeof(*data->objects), "vector of t_object");
	if (data->objects == NULL)
		return (rt_print_error(ERROR_SYSTEM));
	while (true)
	{
		line = get_next_line(fd);
		if (ft_any_error())
			return (rt_print_error(ERROR_SYSTEM));
		if (line == NULL)
			break ;
		rt_skip_whitespace(&line);
		if (*line == '\0' || *line == '#')
			continue ;
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
	char	*scene_path;
	int		fd;

	scene_path = argv[1];
	if (!ft_str_ends_with(scene_path, ".rt"))
		return (rt_print_error(ERROR_INVALID_SCENE_NAME));
	fd = open(scene_path, O_RDONLY);
	if (fd == SYSTEM_ERROR_STATUS)
		return (rt_print_error(ERROR_CANT_READ_SCENE_FILE));
	if (rt_parse_scene_file(fd, data) == ERROR)
	{
		close(fd);
		return (ERROR);
	}
	close(fd);
	if (rt_check_capitalized_object_counts(data->objects) == ERROR)
		return (ERROR);
	return (OK);
}
