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

void	check_leaks(void)
{
	system("leaks -q miniRT");
}

void	key_press_hook(mlx_key_data_t keydata, void *param)
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

t_status	rt_parse_scene_file(int fd, t_data *data)
{
	(void)fd;
	(void)data;
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
	data->mlx = mlx_init(500, 500, WINDOW_TITLE, false);
	if (data->mlx == NULL || !mlx_loop_hook(data->mlx, &rt_draw_loop, NULL))
		return (rt_print_error(ERROR_SYSTEM));
	mlx_key_hook(data->mlx, &key_press_hook, data);
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
