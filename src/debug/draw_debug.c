/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_debug.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/16 18:20:32 by sbos          #+#    #+#                 */
/*   Updated: 2023/02/16 18:20:32 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#include "../MLX42/src/font/font.h"

static char	*rt_get_allocation_count_string(void)
{
	char	*string;
	char	*string_full;

	string = ft_itoa((t_i32)ft_get_allocation_count());
	if (string == NULL)
		return (NULL);
	string_full = ft_strjoin("Allocation count: ", string);
	ft_free(&string);
	return (string_full);
}

t_status	rt_draw_allocation_count(t_data *data)
{
	static mlx_image_t	*image;
	char				*string;

	if (image != NULL)
		mlx_delete_image(data->mlx, image);
	if (!data->draw_debug)
		return (OK);
	string = rt_get_allocation_count_string();
	if (string == NULL)
		return (ERROR);
	image = mlx_put_string(data->mlx, string, 0, FONT_HEIGHT);
	ft_free(&string);
	if (image == NULL)
		return (rt_print_error(ERROR_MLX));
	mlx_set_instance_depth(&image->instances[0], DEBUG_DRAWING_DEPTH);
	return (OK);
}

static char	*rt_get_fps_string(t_data *data)
{
	char	*string;
	char	*string_full;

	string = ft_itoa((t_i32)(1 / data->mlx->delta_time));
	if (string == NULL)
		return (NULL);
	string_full = ft_strjoin(string, " FPS");
	ft_free(&string);
	return (string_full);
}

t_status	rt_draw_fps(t_data *data)
{
	static mlx_image_t	*image; // TODO: See if we still want this to be static?
	char				*string;

	if (image != NULL)
		mlx_delete_image(data->mlx, image);
	if (!data->draw_debug)
		return (OK);
	string = rt_get_fps_string(data);
	if (string == NULL)
		return (rt_print_error(ERROR_SYSTEM));
	image = mlx_put_string(data->mlx, string, 0, 0);
	ft_free(&string);
	if (image == NULL)
		return (rt_print_error(ERROR_MLX));
	mlx_set_instance_depth(&image->instances[0], DEBUG_DRAWING_DEPTH);
	return (OK);
}
