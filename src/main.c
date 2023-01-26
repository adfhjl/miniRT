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

#pragma clang optimize off
#pragma GCC            optimize("O0")

// __AFL_FUZZ_INIT();

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

static int	run(int argc, char *argv[])
{
	t_data	data;

	// void	*ptr = malloc(1);
	// free(ptr);
	// free(ptr);
	// printf("%p\n", ptr);
	// printf("foo\n");
	if (rt_init(argc, argv, &data) == ERROR)
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

int	main(int argc, char *argv[])
{
	// ssize_t len;
	// char buf[100];

// #ifdef __AFL_HAVE_MANUAL_CONTROL // TODO: ADD BACK
//   __AFL_INIT();
// #endif

	// unsigned char *buf = __AFL_FUZZ_TESTCASE_BUF;

	// while (__AFL_LOOP(10000)) { // TODO: ADD BACK

	// memset(buf, 0, sizeof(buf));
	// len = read(0, buf, sizeof(buf));

	// if (len < 8) continue;

	// if (buf[0] == 'f') {

	// 	printf("one\n");
	// 	if (buf[1] == 'o') {

	// 		printf("two\n");
	// 		if (buf[2] == 'o') {

	// 			printf("three\n");
	// 			if (buf[3] == '!') {

	// 				printf("four\n");
	// 				if (buf[4] == '!') {

	// 					printf("five\n");
	// 					if (buf[5] == '!') {

	// 						printf("six\n");
	// 						abort();
	// 					}
	// 				}
	// 			}
	// 		}
	// 	}
	// }
		// size_t len = __AFL_FUZZ_TESTCASE_LEN;  // don't use the macro directly in a
											// call!

		/* Setup function call, e.g. struct target *tmp = libtarget_init() */
		/* Call function to be fuzzed, e.g.: */
		// printf("input: %zd \"%s\"\n", len, buf);
		// run(argc, argv);
		run(2, argv);

		// t_data	data;
		// rt_init(2, argv, &data);

		/* Reset state. e.g. libtarget_free(tmp) */

	// }

	return (EXIT_SUCCESS);
}
