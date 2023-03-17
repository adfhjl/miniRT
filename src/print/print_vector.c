/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_vector.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 19:17:06 by sbos          #+#    #+#                 */
/*   Updated: 2023/03/17 19:17:06 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rt_structs.h"

#include <stdio.h>

void	rt_print_vector(t_vector v)
{
	printf(" %.2f,%.2f,%.2f", v.x, v.y, v.z);
}
