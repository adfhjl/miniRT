/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   assert_normal.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/28 14:21:09 by sbos          #+#    #+#                 */
/*   Updated: 2023/02/28 14:21:09 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rt_structs.h"

#include "vectors/rt_vectors.h"

#include "assert.h" // TODO: REMOVE
#include "stdio.h" // TODO: REMOVE

#define MAG_EPSILON 0.000001

void	rt_assert_normal(t_vector vector, char *location)
{
	t_vector	normalized;
	float		mag;

	normalized = rt_normalized(vector);
	mag = rt_mag(normalized);
	if (!(mag > 1 - MAG_EPSILON && mag < 1 + MAG_EPSILON))
	{
		printf("location: %s\n", location);
		printf("mag: %f, vector: (%f,%f,%f), normalized: (%f,%f,%f)\n",
			mag,
			vector.x, vector.y, vector.z,
			normalized.x, normalized.y, normalized.z);
		assert(mag > 1 - MAG_EPSILON && mag < 1 + MAG_EPSILON);
	}
}
