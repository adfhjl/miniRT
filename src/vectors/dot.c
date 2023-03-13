/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dot.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbenneko <vbenneko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 16:37:41 by vbenneko      #+#    #+#                 */
/*   Updated: 2023/01/24 16:38:05 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rt_structs.h"

float	rt_dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
