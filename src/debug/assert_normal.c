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

#define MAG_EPSILON 0.000001

// TODO: Comment this ifdef stuff back in
// #ifdef DEBUG
void	rt_assert_normal(t_vector vector)
{
	t_vector	normalized;
	float		mag;

	normalized = rt_normalized(vector);
	mag = rt_mag(normalized);
	assert(mag > 1 - MAG_EPSILON && mag < 1 + MAG_EPSILON);
	// assert(vector.x == normalized.x);
	// assert(vector.y == normalized.y);
	// assert(vector.z == normalized.z);
}
// #else
// void	rt_assert_normal(t_vector vector)
// {
// 	(void)vector;
// }
// #endif
