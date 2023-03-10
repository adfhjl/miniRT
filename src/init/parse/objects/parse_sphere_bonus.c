/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_sphere_bonus.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 15:40:10 by sbos          #+#    #+#                 */
/*   Updated: 2023/01/24 15:40:10 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rt_structs.h"

#include "init/parse/objects/rt_parse_objects.h"

t_status	rt_parse_sphere(char **line_ptr, t_object *sphere)
{
	if (rt_parse_sphere_basics(line_ptr, sphere) == ERROR
	|| rt_parse_material(line_ptr, &sphere->material) == ERROR)
		return (ERROR);
	return (OK);
}
