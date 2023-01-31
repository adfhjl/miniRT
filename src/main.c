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
#include "init/rt_init.h"
#include <limits.h> // TODO: REMOVE

__AFL_FUZZ_INIT();

// void	rt_check_leaks(void)
// {
// 	system("leaks -q miniRT");
// }

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

#include <stdio.h>

static int	run(int argc, char *argv[], char *buf)
{
	t_data	data;

	// void	*ptr = malloc(1);
	// free(ptr);
	// free(ptr);
	// printf("%p\n", ptr);
	// printf("foo\n");
	if (rt_init(argc, argv, &data, buf) == ERROR)
	{
		// printf("bar\n");
		rt_cleanup(&data);
		return (EXIT_FAILURE);
	}
	// printf("baz\n");
	// mlx_loop(data.mlx);
	rt_cleanup(&data);
	return (EXIT_SUCCESS);
}

// TODO: Is this necessary?
#pragma clang optimize off
#pragma GCC            optimize("O0")

int	main(int argc, char *argv[])
{
#ifdef __AFL_HAVE_MANUAL_CONTROL
  __AFL_INIT();
#endif

	#ifdef GCOV
	unsigned char buf[1024];
	ft_bzero(buf, sizeof(buf));
	if (read(0, buf, sizeof(buf) - 1) == -1)
	{
		perror("read()");
		return (EXIT_FAILURE);
	}
	#else
	unsigned char *buf = __AFL_FUZZ_TESTCASE_BUF;
	#endif

	while (__AFL_LOOP(UINT_MAX)) {
		run(2, argv, buf);
	}

	return (EXIT_SUCCESS);
}
