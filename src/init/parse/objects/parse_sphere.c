/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_sphere.c                                     :+:    :+:            */
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

static void	rt_set_non_bonus_defines(t_object *sphere)
{
	sphere->material.emissive = rt_scale(sphere->material.rgb, SPHERE_EMISSIVE_FACTOR);
	sphere->material.specular_chance = SPHERE_SPECULAR_CHANCE;
	sphere->material.specular_roughness = SPHERE_SPECULAR_ROUGHNESS;
	sphere->material.index_of_refraction = SPHERE_INDEX_OF_REFRACTION;
	sphere->material.refraction_chance = SPHERE_REFRACTION_CHANCE;
	sphere->material.refraction_roughness = SPHERE_REFRACTION_ROUGHNESS;
}

t_status	rt_parse_sphere(char **line_ptr, t_object *sphere)
{
	if (rt_parse_vector(line_ptr, &sphere->pos) == ERROR
		|| rt_check_separating_whitespace(line_ptr) == ERROR
		|| rt_parse_float(line_ptr, &sphere->diameter) == ERROR
		|| rt_check_separating_whitespace(line_ptr) == ERROR
		|| rt_parse_rgb(line_ptr, &sphere->material.rgb) == ERROR)
		return (ERROR);
	rt_set_non_bonus_defines(sphere);
	return (OK);
}
