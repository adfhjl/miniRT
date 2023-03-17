/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_material_bonus.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/10 20:35:53 by sbos          #+#    #+#                 */
/*   Updated: 2023/03/10 20:35:53 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rt_structs.h"

#include "init/parse/objects/rt_parse_objects.h"
#include "init/parse/rt_parse.h"
#include "vectors/rt_vectors.h"

t_status	rt_parse_material(char **line_ptr, t_material *material)
{
	if (rt_check_separating_whitespace(line_ptr) == ERROR
		|| rt_parse_rgb(line_ptr, &material->emissive_original) == ERROR
		|| rt_check_separating_whitespace(line_ptr) == ERROR
		|| rt_parse_range_float(line_ptr, &material->specular_chance,
			0, 1) == ERROR
		|| rt_check_separating_whitespace(line_ptr) == ERROR
		|| rt_parse_range_float(line_ptr, &material->specular_roughness,
			0, 1) == ERROR
		|| rt_check_separating_whitespace(line_ptr) == ERROR
		|| rt_parse_float(line_ptr, &material->index_of_refraction) == ERROR
		|| rt_check_separating_whitespace(line_ptr) == ERROR
		|| rt_parse_range_float(line_ptr, &material->refraction_chance,
			0, 1) == ERROR
		|| rt_check_separating_whitespace(line_ptr) == ERROR
		|| rt_parse_range_float(line_ptr, &material->refraction_roughness,
			0, 1) == ERROR
		|| rt_check_separating_whitespace(line_ptr) == ERROR
		|| rt_parse_vector(line_ptr, &material->line_frequency) == ERROR
		|| rt_check_separating_whitespace(line_ptr) == ERROR
		|| rt_parse_vector(line_ptr, &material->line_offset) == ERROR)
		return (ERROR);
	return (OK);
}
