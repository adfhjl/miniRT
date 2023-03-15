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

#include "init/parse/objects/rt_parse_objects.h"
#include "vectors/rt_vectors.h"

static void	rt_set_non_bonus_defines(t_object *light)
{
	light->diameter = LIGHT_DIAMETER;
	light->material.specular_chance = LIGHT_SPECULAR_CHANCE;
	light->material.specular_roughness = LIGHT_SPECULAR_ROUGHNESS;
	light->material.index_of_refraction = LIGHT_INDEX_OF_REFRACTION;
	light->material.refraction_chance = LIGHT_REFRACTION_CHANCE;
	light->material.refraction_roughness = LIGHT_REFRACTION_ROUGHNESS;
}

t_status	rt_parse_light(char **line_ptr, t_object *light)
{
	if (rt_parse_light_basics(line_ptr, light) == ERROR)
		return (ERROR);
	rt_set_non_bonus_defines(light);
	light->material.emissive = rt_scale(rt_scale(light->material.rgb, LIGHT_EMISSIVE_FACTOR), light->ratio);
	return (OK);
}
