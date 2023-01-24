/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_camera.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 15:40:10 by sbos          #+#    #+#                 */
/*   Updated: 2023/01/24 15:40:10 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "init/parse/rt_parse.h"

t_status	rt_parse_camera(char **line_ptr, t_object *object)
{
	if (rt_parse_vector(line_ptr, &object->camera.coordinates) == ERROR)
		return (ERROR);
	if (!ft_chr_in_str(**line_ptr, WHITESPACE))
		return (rt_print_error(ERROR_EXPECTED_WHITESPACE));
	if (rt_parse_vector(line_ptr, &object->camera.orientation) == ERROR)
		return (ERROR);
	if (!ft_chr_in_str(**line_ptr, WHITESPACE))
		return (rt_print_error(ERROR_EXPECTED_WHITESPACE));
	if (rt_parse_range_float(line_ptr, &object->camera.fov, 0, 180) == ERROR)
		return (ERROR);
	return (OK);
}
