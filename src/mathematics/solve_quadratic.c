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

#include "minirt.h"

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
	q.solution_negative = (-b - sqrtf(discriminant)) / 2 * a;
	q.solution_positive = (-b + sqrtf(discriminant)) / 2 * a;
	if (q.solution_negative < 0 && q.solution_positive < 0)
		q.solution = false;
	return (q);
}
