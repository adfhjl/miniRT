/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 14:21:07 by sbos          #+#    #+#                 */
/*   Updated: 2023/01/24 14:21:07 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "init/parse/rt_parse.h"
#include "debug/rt_debug.h"

// static void	rt_key_hook(mlx_key_data_t keydata, void *param)
// {
// 	t_data	*data;

// 	data = param;
// 	if (keydata.action != MLX_PRESS)
// 		return ;
// 	if (keydata.key == MLX_KEY_ESCAPE)
// 		mlx_close_window(data->mlx);
// }

// static void	rt_draw_loop(void *param)
// {
// 	(void)param;
// }

static t_object	*rt_get_object_ptr(t_object_type searched_object_type,
					t_object *objects)
{
	size_t	object_index;
	size_t	size;

	object_index = 0;
	size = ft_vector_get_size(objects);
	while (object_index < size)
	{
		if (objects[object_index].type == searched_object_type)
			return (&objects[object_index]);
		object_index++;
	}
	return (NULL);
}

static void	rt_assign_capitalized_objects(t_data *data)
{
	data->ambient
		= &rt_get_object_ptr(OBJECT_TYPE_AMBIENT, data->objects)->ambient;
	data->camera
		= &rt_get_object_ptr(OBJECT_TYPE_CAMERA, data->objects)->camera;
	data->light
		= &rt_get_object_ptr(OBJECT_TYPE_LIGHT, data->objects)->light;
}

t_status	rt_init(int argc, char *argv[], t_data *data)
{
	ft_bzero(data, sizeof(*data));
	if (argc != 2)
		return (rt_print_error(ERROR_INVALID_ARGC));
	if (rt_parse_argv(argv, data) == ERROR)
		return (ERROR);
	rt_assign_capitalized_objects(data);
	rt_debug_print_objects(data);
	// data->mlx = mlx_init(500, 500, WINDOW_TITLE, false);
	// if (data->mlx == NULL || !mlx_loop_hook(data->mlx, &rt_draw_loop, NULL))
	// 	return (rt_print_error(ERROR_SYSTEM));
	// mlx_key_hook(data->mlx, &rt_key_hook, data);
	return (OK);
}
