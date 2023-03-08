/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lerp.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/02 18:48:36 by sbos          #+#    #+#                 */
/*   Updated: 2023/03/02 18:48:36 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Linear blend where an interpolation of 0.0f means old is returned,
// while 1.0f means new_ is returned.
float	rt_lerp(float old, float new_, float t)
{
	return (old * (1 - t) + new_ * t);
}
