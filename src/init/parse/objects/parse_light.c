/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_light.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 15:40:10 by sbos          #+#    #+#                 */
/*   Updated: 2023/01/24 15:40:10 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rt_non_bonus_defines.h"
#include "rt_structs.h"

#include "init/parse/rt_parse.h"
#include "init/parse/objects/rt_parse_objects.h"
#include "vectors/rt_vectors.h"

t_status	rt_parse_light(char **line_ptr, t_object *light)
{
	if (rt_parse_vector(line_ptr, &light->pos) == ERROR
		|| rt_check_separating_whitespace(line_ptr) == ERROR
		|| rt_parse_range_float(line_ptr, &light->ratio, 0, 1) == ERROR
		|| rt_check_separating_whitespace(line_ptr) == ERROR
		|| rt_parse_rgb(line_ptr, &light->material.rgb) == ERROR)
		return (ERROR);
	light->diameter = LIGHT_DIAMETER;
	// TODO: Can I get rid of LIGHT_EMISSIVE_FACTOR?
	// light->material.emissive = rt_scale(rt_scale(light->material.rgb, light->ratio), LIGHT_EMISSIVE_FACTOR);

	// // TODO: Do I want this?
	// light->material.rgb = (t_rgb){0, 0, 0};

	return (OK);
}
