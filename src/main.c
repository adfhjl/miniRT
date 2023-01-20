/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbenneko <vbenneko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/16 14:56:22 by vbenneko      #+#    #+#                 */
/*   Updated: 2023/01/19 18:40:42 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "debug/rt_debug.h"

void	check_leaks(void)
{
	system("leaks -q miniRT");
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(data->mlx);
}

void	rt_draw_loop(void *param)
{
	(void)param;
}

void	rt_cleanup(t_data *data)
{
	// TODO: In so_long I had to create a texture and free it manually.
	// I presume that this same code snippet is necessary for this project.
	// if (data->texture.data != NULL)
	// 	mlx_delete_texture(data->texture.data);
	if (data->mlx != NULL)
		mlx_terminate(data->mlx);
	ft_free_allocations();
}

// TODO: Should this also be able to handle doubles?
t_status	rt_parse_float(char *token, float *field_ptr)
{
	(void)token;
	(void)field_ptr;
	if (true)
		return (rt_print_error(ERROR_FAILED_TO_PARSE_FLOAT));
	return (OK);
}

t_status	rt_parse_vector(char *token, t_vector *vector)
{
	if (rt_parse_float(token, &vector->x) == ERROR)
		return (ERROR);
	if (*token != ',')
		return (rt_print_error(ERROR_EXPECTED_COMMA));
	if (rt_parse_float(token, &vector->y) == ERROR)
		return (ERROR);
	if (*token != ',')
		return (rt_print_error(ERROR_EXPECTED_COMMA));
	if (rt_parse_float(token, &vector->z) == ERROR)
		return (ERROR);
	if (*token == ',')
		return (rt_print_error(ERROR_UNEXPECTED_COMMA));
	return (OK);
}

t_status	rt_parse_char(char *token, unsigned char *field_ptr)
{
	int	nbr;

	if (!ft_atoi_safe(token, &nbr) || nbr < 0 || nbr > 255)
		return (rt_print_error(ERROR_FAILED_TO_PARSE_CHAR));
	*field_ptr = (unsigned char)nbr;
	return (OK);
}

t_status	rt_parse_rgb(char *token, t_rgb *rgb)
{
	if (rt_parse_char(token, &rgb->r) == ERROR)
		return (ERROR);
	if (*token != ',')
		return (rt_print_error(ERROR_EXPECTED_COMMA));
	if (rt_parse_char(token, &rgb->g) == ERROR)
		return (ERROR);
	if (*token != ',')
		return (rt_print_error(ERROR_EXPECTED_COMMA));
	if (rt_parse_char(token, &rgb->b) == ERROR)
		return (ERROR);
	if (*token == ',')
		return (rt_print_error(ERROR_UNEXPECTED_COMMA));
	return (OK);
}

t_status	rt_parse_field(char *token, t_object *object,
				t_parsing_state *state)
{
	if (object->type == OBJECT_TYPE_AMBIENT)
	{
		if (*state == PARSING_STATE_TYPE)
		{
			*state = PARSING_STATE_RATIO;
			if (rt_parse_float(token, &object->ambient.ratio) == ERROR)
				return (ERROR);
		}
		else if (*state == PARSING_STATE_RATIO)
		{
			*state = PARSING_STATE_END;
			if (rt_parse_rgb(token, &object->ambient.rgb) == ERROR)
				return (ERROR);
		}
	}
	else if (object->type == OBJECT_TYPE_CAMERA)
	{
		if (*state == PARSING_STATE_TYPE)
		{
			*state = PARSING_STATE_COORDINATES;
			if (rt_parse_vector(token, &object->camera.coordinates) == ERROR)
				return (ERROR);
		}
		else if (*state == PARSING_STATE_COORDINATES)
		{
			*state = PARSING_STATE_ORIENTATION;
			if (rt_parse_vector(token, &object->camera.orientation) == ERROR)
				return (ERROR);
		}
		else if (*state == PARSING_STATE_ORIENTATION)
		{
			*state = PARSING_STATE_END;
			if (rt_parse_char(token, &object->camera.fov) == ERROR)
				return (ERROR);
		}
	}
	else if (object->type == OBJECT_TYPE_LIGHT)
	{
		if (*state == PARSING_STATE_TYPE)
		{
			*state = PARSING_STATE_COORDINATES;
			if (rt_parse_vector(token, &object->light.coordinates) == ERROR)
				return (ERROR);
		}
		else if (*state == PARSING_STATE_COORDINATES)
		{
			*state = PARSING_STATE_END;
			if (rt_parse_float(token, &object->light.brightness) == ERROR)
				return (ERROR);
		}
	}
	else if (object->type == OBJECT_TYPE_SPHERE)
	{
		if (*state == PARSING_STATE_TYPE)
		{
			*state = PARSING_STATE_COORDINATES;
			if (rt_parse_vector(token, &object->sphere.center) == ERROR)
				return (ERROR);
		}
		else if (*state == PARSING_STATE_COORDINATES)
		{
			*state = PARSING_STATE_DIAMETER;
			if (rt_parse_float(token, &object->sphere.diameter) == ERROR)
				return (ERROR);
		}
		else if (*state == PARSING_STATE_DIAMETER)
		{
			*state = PARSING_STATE_END;
			if (rt_parse_rgb(token, &object->sphere.rgb) == ERROR)
				return (ERROR);
		}
	}
	else if (object->type == OBJECT_TYPE_PLANE)
	{
		if (*state == PARSING_STATE_TYPE)
		{
			*state = PARSING_STATE_COORDINATES;
			if (rt_parse_vector(token, &object->plane.coordinates) == ERROR)
				return (ERROR);
		}
		else if (*state == PARSING_STATE_COORDINATES)
		{
			*state = PARSING_STATE_ORIENTATION;
			if (rt_parse_vector(token, &object->plane.orientation) == ERROR)
				return (ERROR);
		}
		else if (*state == PARSING_STATE_ORIENTATION)
		{
			*state = PARSING_STATE_END;
			if (rt_parse_rgb(token, &object->plane.rgb) == ERROR)
				return (ERROR);
		}
	}
	else if (object->type == OBJECT_TYPE_CYLINDER)
	{
		if (*state == PARSING_STATE_TYPE)
		{
			*state = PARSING_STATE_COORDINATES;
			if (rt_parse_vector(token, &object->cylinder.coordinates) == ERROR)
				return (ERROR);
		}
		else if (*state == PARSING_STATE_COORDINATES)
		{
			*state = PARSING_STATE_ORIENTATION;
			if (rt_parse_vector(token, &object->cylinder.orientation) == ERROR)
				return (ERROR);
		}
		else if (*state == PARSING_STATE_ORIENTATION)
		{
			*state = PARSING_STATE_DIAMETER;
			if (rt_parse_float(token, &object->cylinder.diameter) == ERROR)
				return (ERROR);
		}
		else if (*state == PARSING_STATE_DIAMETER)
		{
			*state = PARSING_STATE_HEIGHT;
			if (rt_parse_float(token, &object->cylinder.height) == ERROR)
				return (ERROR);
		}
		else if (*state == PARSING_STATE_HEIGHT)
		{
			*state = PARSING_STATE_END;
			if (rt_parse_rgb(token, &object->cylinder.rgb) == ERROR)
				return (ERROR);
		}
	}
	else
		return (rt_print_error(ERROR_UNREACHABLE));

	return (OK);
}

void	rt_skip_non_whitespace(char **line_ptr)
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

void	rt_skip_whitespace(char **line_ptr)
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
		token = rt_parse_token(&line);
		if (token == NULL)
			return (ERROR);

		if (state == PARSING_STATE_END)
			return (rt_print_error(ERROR_UNEXPECTED_EXTRA_FIELD));

		if (rt_parse_field(token, object, &state) == ERROR)
			return (ERROR);

		// TODO: May need to move this up
		if (line == '\0')
			break ;
	}
	return (OK);
}

t_status	rt_parse_scene_file(int fd, t_data *data)
{
	t_object	object;
	char		*line;

	data->objects = ft_vector_new(sizeof(*data->objects));
	if (data->objects == NULL)
		return (rt_print_error(ERROR_SYSTEM));

	{
		line = get_next_line(fd);
		// TODO: Is there a way to tell whether gnl just reached eof vs. errored?
		if (line == NULL)
			return (rt_print_error(ERROR_SYSTEM));
		ft_bzero(&object, sizeof(object));
		if (rt_parse_object(line, &object) == ERROR)
			return (ERROR);

		// TODO: Not sure if I want to do this here or loop through the objects later,
		// but I need to make sure that any second encountered A/C/L throws an error

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

t_status	rt_init(int argc, char *argv[], t_data *data)
{
	ft_bzero(data, sizeof(*data));
	if (argc != 2)
		return (rt_print_error(ERROR_INVALID_ARGC));
	if (rt_parse_argv(argv, data) == ERROR)
		return (ERROR);
	rt_debug_print_objects(data);
	data->mlx = mlx_init(500, 500, WINDOW_TITLE, false);
	if (data->mlx == NULL || !mlx_loop_hook(data->mlx, &rt_draw_loop, NULL))
		return (rt_print_error(ERROR_SYSTEM));
	mlx_key_hook(data->mlx, &key_hook, data);
	return (OK);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	atexit(check_leaks);
	if (rt_init(argc, argv, &data) == ERROR)
	{
		rt_cleanup(&data);
		return (EXIT_FAILURE);
	}
	mlx_loop(data.mlx);
	rt_cleanup(&data);
	return (EXIT_SUCCESS);
}
