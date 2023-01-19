/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbenneko <vbenneko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/16 14:56:22 by vbenneko      #+#    #+#                 */
/*   Updated: 2023/01/16 17:29:39 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_leaks(void)
{
	system("leaks -q miniRT");
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

t_status	rt_parse_argv(int argc, char *argv[])
{
	if (argc != 2)
		return (rt_print_error(ERROR_INVALID_ARGC));
	(void)argv;
	return (OK);
}

t_status	rt_init(int argc, char *argv[], t_data *data)
{
	ft_bzero(data, sizeof(*data));
	if (rt_parse_argv(argc, argv) == ERROR)
		return (ERROR);
	data->mlx = mlx_init(500, 500, WINDOW_TITLE, false);
	if (data->mlx == NULL || !mlx_loop_hook(data->mlx, &rt_draw_loop, NULL))
		return (rt_print_error(ERROR_SYSTEM));
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
