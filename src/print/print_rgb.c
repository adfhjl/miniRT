/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_rgb.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 19:22:16 by sbos          #+#    #+#                 */
/*   Updated: 2023/03/17 19:22:16 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rt_structs.h"

#include <stdio.h>

void	rt_print_rgb(t_rgb rgb)
{
	int	r;
	int	g;
	int	b;

	r = (int)(rgb.r * 255);
	g = (int)(rgb.g * 255);
	b = (int)(rgb.b * 255);
	printf(" %i,%i,%i", r, g, b);
}
