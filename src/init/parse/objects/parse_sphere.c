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

#include "init/parse/objects/rt_parse_objects.h"
#include "vectors/rt_vectors.h"

static void	rt_set_non_bonus_defines(t_object *sphere)
{
	sphere->material.specular_chance = SPHERE_SPECULAR_CHANCE;
	sphere->material.specular_roughness = SPHERE_SPECULAR_ROUGHNESS;
	sphere->material.index_of_refraction = SPHERE_INDEX_OF_REFRACTION;
	sphere->material.refraction_chance = SPHERE_REFRACTION_CHANCE;
	sphere->material.refraction_roughness = SPHERE_REFRACTION_ROUGHNESS;
}

t_status	rt_parse_sphere(char **line_ptr, t_object *sphere)
{
	if (rt_parse_sphere_basics(line_ptr, sphere) == ERROR)
		return (ERROR);
	sphere->material.emissive = (t_vector){0, 0, 0};
	rt_set_non_bonus_defines(sphere);
	return (OK);
}
