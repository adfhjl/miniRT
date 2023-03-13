/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   solve_quadratic.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/28 18:37:03 by sbos          #+#    #+#                 */
/*   Updated: 2023/02/28 18:37:03 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rt_structs.h"

#include <math.h>

// Note: If a is positive, solution_plus >= solution_minus
//       If a is negtive, solution_minus >= solution_plus
t_quadratic	rt_solve_quadratic(float a, float b, float c)
{
	t_quadratic	q;
	float		discriminant;

	q.solution = true;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	{
		q.solution = false;
		return (q);
	}
	q.solution_minus = (-b - sqrtf(discriminant)) / (2 * a);
	q.solution_plus = (-b + sqrtf(discriminant)) / (2 * a);
	if (q.solution_minus < 0 && q.solution_plus < 0)
		q.solution = false;
	return (q);
}
