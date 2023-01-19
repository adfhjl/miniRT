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

#include "MLX42/MLX42.h"
#include "libft.h"
#include "minirt.h"

void	draw_loop(void *param)
{
	(void)param;
}

int	main(void)
{
	mlx_t	*mlx;

	mlx = mlx_init(500, 500, PROGRAM_NAME, false);
	if (mlx == NULL || mlx_loop_hook(mlx, &draw_loop, NULL) == false)
		return (EXIT_FAILURE);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
