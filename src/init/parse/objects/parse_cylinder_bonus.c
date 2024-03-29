/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_cylinder_bonus.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 15:40:10 by sbos          #+#    #+#                 */
/*   Updated: 2023/01/24 15:40:10 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rt_structs.h"

#include "init/parse/objects/rt_parse_objects.h"

t_status	rt_parse_cylinder(char **line_ptr, t_object *cylinder)
{
	if (rt_parse_cylinder_basics(line_ptr, cylinder) == ERROR
		|| rt_parse_material(line_ptr, &cylinder->material) == ERROR)
		return (ERROR);
	return (OK);
}
