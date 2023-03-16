/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color_conversion.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/02 18:38:50 by sbos          #+#    #+#                 */
/*   Updated: 2023/03/02 18:38:50 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rt_structs.h"

#include "rgb/rt_rgb.h"
#include "utils/rt_utils.h"
#include "vectors/rt_vectors.h"

#include <math.h>

static t_rgb	rt_pow(t_rgb a, float b)
{
	return ((t_rgb){
		powf(a.r, b),
		powf(a.g, b),
		powf(a.b, b)});
}

static t_rgb	rt_mix_linear(t_rgb a, t_rgb b, t_rgb t)
{
	return ((t_rgb){
		rt_lerp(a.r, b.r, t.r),
		rt_lerp(a.g, b.g, t.g),
		rt_lerp(a.b, b.b, t.b),
	});
}

static t_rgb	rt_less_than(t_rgb f, float value)
{
	t_rgb	rgb;

	rgb.r = 0;
	if (f.r < value)
		rgb.r = 1;
	rgb.g = 0;
	if (f.g < value)
		rgb.g = 1;
	rgb.b = 0;
	if (f.b < value)
		rgb.b = 1;
	return (rgb);
}

t_rgb	rt_linear_to_srgb(t_rgb rgb)
{
    rgb = rt_clamp_rgb(rgb, 0.0f, 1.0f);

    return rt_mix_linear(
        rt_add_scalar_rgb(rt_scale(rt_pow(rgb, 1.0f / 2.4f), 1.055f), -0.055f),
        rt_scale(rgb, 12.92f),
        rt_less_than(rgb, 0.0031308f)
    );
}

t_rgb	rt_srgb_to_linear(t_rgb rgb)
{
    rgb = rt_clamp_rgb(rgb, 0.0f, 1.0f);

    return rt_mix_linear(
        rt_pow(rt_scale(rt_add_scalar_rgb(rgb, 0.055f), 1.0f / 1.055f), 2.4f),
        rt_scale(rgb, 1.0f / 12.92f),
        rt_less_than(rgb, 0.04045f)
    );
}
