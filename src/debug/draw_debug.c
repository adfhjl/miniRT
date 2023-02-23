/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_debug.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/16 18:20:32 by sbos          #+#    #+#                 */
/*   Updated: 2023/02/22 17:32:17 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#include "../MLX42/src/font/font.h"

static char	*rt_get_nbr_string(int nbr, char *appended_string)
{
	char	*nbr_string;
	char	*nbr_string_full;

	nbr_string = ft_itoa(nbr);
	if (nbr_string == NULL)
		return (NULL);
	nbr_string_full = ft_strjoin(nbr_string, appended_string);
	ft_free(&nbr_string);
	return (nbr_string_full);
}

static t_status	rt_draw_debug_line(t_data *data, mlx_image_t **images_ptr,
					int nbr, char *appended_string)
{
	char	*string;

	if (images_ptr[data->debug_image_index] != NULL)
		mlx_delete_image(data->mlx, images_ptr[data->debug_image_index]);
	if (data->draw_debug)
	{
		string = rt_get_nbr_string(nbr, appended_string);
		if (string == NULL)
			return (rt_print_error(ERROR_SYSTEM));
		images_ptr[data->debug_image_index] = mlx_put_string(data->mlx, string, 0, FONT_HEIGHT * (int)data->debug_image_index);
		ft_free(&string);
		if (images_ptr[data->debug_image_index] == NULL)
			return (rt_print_error(ERROR_MLX));
		mlx_set_instance_depth(&images_ptr[data->debug_image_index]->instances[0], DEBUG_DRAWING_DEPTH);
	}
	data->debug_image_index++;
	return (OK);
}

t_status	rt_draw_debug_lines(t_data *data)
{
	static mlx_image_t	*images[4] = {0};

	data->debug_image_index = 0;
	rt_draw_debug_line(data, images, (int)(1 / data->mlx->delta_time), " frames/s");
	rt_draw_debug_line(data, images, (int)(1000 * data->mlx->delta_time), " ms/frame");
	rt_draw_debug_line(data, images, (int)ft_get_allocation_count(), " allocations");
	rt_draw_debug_line(data, images, (int)ft_get_bytes_allocated(), " bytes allocated");
	return (OK);
}
