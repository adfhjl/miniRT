/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   aces_film.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/03 18:14:54 by sbos          #+#    #+#                 */
/*   Updated: 2023/03/03 18:14:54 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rgb/rt_rgb.h"
#include "vectors/rt_vectors.h"

// ACES tone mapping curve fit to go from HDR to LDR
// https://knarkowicz.wordpress.com/2016/01/06/aces-filmic-tone-mapping-curve/
// return clamp(
//   (
//     a*(a*2.51f + 0.03f)
//   )
//   /
//   (
//     a*(a*2.43f + 0.59f) + 0.14f
//   ),
//   0.0f,
//   1.0f
// );
t_rgb	rt_aces_film(t_rgb a)
{
	t_rgb	b;
	t_rgb	c;

	b = rt_scale(a, 2.51f);
	b = rt_add_scalar_rgb(b, 0.03f);
	b = rt_multiply_rgb(a, b);

	c = rt_scale(a, 2.43f);
	c = rt_add_scalar_rgb(c, 0.59f);
	c = rt_multiply_rgb(a, c);
	c = rt_add_scalar_rgb(c, 0.14f);

	b = rt_divide_rgb(b, c);
	return (rt_clamp_rgb(b, 0.0f, 1.0f));
}
