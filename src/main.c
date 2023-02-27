/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbenneko <vbenneko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/16 14:56:22 by vbenneko      #+#    #+#                 */
/*   Updated: 2023/02/06 18:07:29 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#include "init/rt_init.h"

#include <stdlib.h> // TODO: REMOVE!

void	rt_check_leaks(void)
{
	system("leaks -q miniRT");
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

int	main(int argc, char *argv[])
{
	static t_data	data;

	atexit(rt_check_leaks);
	if (rt_init(argc, argv, &data) == ERROR)
	{
		rt_cleanup(&data);
		return (EXIT_FAILURE);
	}
	mlx_loop(data.mlx);
	rt_cleanup(&data);
	return (EXIT_SUCCESS);
}
