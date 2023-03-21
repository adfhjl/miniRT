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

#include "libft/src/allocating/ft_allocating.h"

#include "rt_structs.h"

#include "init/rt_init.h"

#include <stdlib.h>

// void	rt_check_leaks(void)
// {
// 	system("leaks -q miniRT");
// }

void	rt_cleanup(t_data *data)
{
	if (data->mlx != NULL)
		mlx_terminate(data->mlx);
	ft_free_allocations();
}

// atexit(rt_check_leaks);
int	main(int argc, char *argv[])
{
	static t_data	data;

	if (rt_init(argc, argv, &data) == ERROR)
	{
		rt_cleanup(&data);
		return (EXIT_FAILURE);
	}
	mlx_loop(data.mlx);
	rt_cleanup(&data);
	return (EXIT_SUCCESS);
}
