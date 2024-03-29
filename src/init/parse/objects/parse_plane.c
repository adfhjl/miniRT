/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_plane.c                                      :+:    :+:            */
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

static void	rt_set_non_bonus_defines(t_object *plane)
{
	plane->material.specular_chance = PLANE_SPECULAR_CHANCE;
	plane->material.specular_roughness = PLANE_SPECULAR_ROUGHNESS;
	plane->material.index_of_refraction = PLANE_INDEX_OF_REFRACTION;
	plane->material.refraction_chance = PLANE_REFRACTION_CHANCE;
	plane->material.refraction_roughness = PLANE_REFRACTION_ROUGHNESS;
}

t_status	rt_parse_plane(char **line_ptr, t_object *plane)
{
	if (rt_parse_plane_basics(line_ptr, plane) == ERROR)
		return (ERROR);
	rt_set_non_bonus_defines(plane);
	return (OK);
}
