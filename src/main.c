/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbenneko <vbenneko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/16 14:56:22 by vbenneko      #+#    #+#                 */
/*   Updated: 2023/02/01 17:50:54 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "init/rt_init.h"

void	rt_check_leaks(void)
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

int	main(int argc, char *argv[])
{
	t_data	data;

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
