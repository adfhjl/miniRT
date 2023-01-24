/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_cylinder.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 15:40:10 by sbos          #+#    #+#                 */
/*   Updated: 2023/01/24 15:40:10 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "init/parse/rt_parse.h"

t_status	rt_parse_cylinder(char **line_ptr, t_object *object)
{
	if (rt_parse_vector(line_ptr, &object->cylinder.coordinates) == ERROR)
		return (ERROR);
	if (!ft_chr_in_str(**line_ptr, WHITESPACE))
		return (rt_print_error(ERROR_EXPECTED_WHITESPACE));
	if (rt_parse_vector(line_ptr, &object->cylinder.orientation) == ERROR)
		return (ERROR);
	if (!ft_chr_in_str(**line_ptr, WHITESPACE))
		return (rt_print_error(ERROR_EXPECTED_WHITESPACE));
	if (rt_parse_float(line_ptr, &object->cylinder.diameter) == ERROR)
		return (ERROR);
	if (!ft_chr_in_str(**line_ptr, WHITESPACE))
		return (rt_print_error(ERROR_EXPECTED_WHITESPACE));
	if (rt_parse_float(line_ptr, &object->cylinder.height) == ERROR)
		return (ERROR);
	if (!ft_chr_in_str(**line_ptr, WHITESPACE))
		return (rt_print_error(ERROR_EXPECTED_WHITESPACE));
	if (rt_parse_rgb(line_ptr, &object->cylinder.rgb) == ERROR)
		return (ERROR);
	return (OK);
}
