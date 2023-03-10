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
#include "init/parse/objects/rt_parse_objects.h"
#include "vectors/rt_vectors.h"

static void	rt_set_non_bonus_defines(t_object *cylinder)
{
	cylinder->material.emissive = rt_scale(cylinder->material.rgb, CYLINDER_EMISSIVE_FACTOR);
	cylinder->material.specular_chance = CYLINDER_SPECULAR_CHANCE;
	cylinder->material.specular_roughness = CYLINDER_SPECULAR_ROUGHNESS;
	cylinder->material.index_of_refraction = CYLINDER_INDEX_OF_REFRACTION;
	cylinder->material.refraction_chance = CYLINDER_REFRACTION_CHANCE;
	cylinder->material.refraction_roughness = CYLINDER_REFRACTION_ROUGHNESS;
}

t_status	rt_parse_cylinder(char **line_ptr, t_object *cylinder)
{
	if (rt_parse_vector(line_ptr, &cylinder->pos) == ERROR
		|| rt_check_separating_whitespace(line_ptr) == ERROR
		|| rt_parse_normal(line_ptr, &cylinder->normal) == ERROR
		|| rt_check_separating_whitespace(line_ptr) == ERROR
		|| rt_parse_float(line_ptr, &cylinder->diameter) == ERROR
		|| rt_check_separating_whitespace(line_ptr) == ERROR
		|| rt_parse_float(line_ptr, &cylinder->height) == ERROR
		|| rt_check_separating_whitespace(line_ptr) == ERROR
		|| rt_parse_rgb(line_ptr, &cylinder->material.rgb) == ERROR)
		return (ERROR);
	rt_set_non_bonus_defines(cylinder);
	return (OK);
}
