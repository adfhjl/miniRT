/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_light_bonus.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 15:40:10 by sbos          #+#    #+#                 */
/*   Updated: 2023/01/24 15:40:10 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rt_structs.h"

#include "init/parse/objects/rt_parse_objects.h"
#include "init/parse/rt_parse.h"
#include "vectors/rt_vectors.h"

t_status	rt_parse_light(char **line_ptr, t_object *light)
{
	if (rt_parse_light_basics(line_ptr, light) == ERROR
	|| rt_check_separating_whitespace(line_ptr) == ERROR
	|| rt_parse_float(line_ptr, &light->diameter) == ERROR
	|| rt_parse_material(line_ptr, &light->material) == ERROR)
		return (ERROR);
	light->material.emissive = rt_scale(light->material.emissive, light->ratio);
	return (OK);
}
