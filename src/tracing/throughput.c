/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   throughput.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/16 18:52:23 by sbos          #+#    #+#                 */
/*   Updated: 2023/03/16 18:52:23 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rt_structs.h"

#include "rgb/rt_rgb.h"
#include "vectors/rt_vectors.h"

// Uses Beer's law to get a multiplier for light that travels
// through the object, to make that light decrease:
// multiplier = e^(-absorb * distance)
t_rgb	rt_absorb(t_hit_info info, t_rgb throughput)
{
	t_rgb	white;
	t_rgb	absorb;
	t_rgb	multiplier;

	white = (t_rgb){1, 1, 1};
	absorb = rt_sub(white, info.material.rgb);
	multiplier = rt_exp_rgb(rt_scale(absorb, -info.distance));
	return (rt_multiply_rgb(throughput, multiplier));
}

t_rgb	rt_update_throughput(float do_refraction, t_rgb rgb, float do_specular,
			t_rgb throughput)
{
	t_rgb	white;
	t_rgb	throughput_factor;

	white = (t_rgb){1, 1, 1};
	if (do_refraction == 0.0f)
	{
		throughput_factor = rt_mix(rgb, white, do_specular);
		throughput = rt_multiply_rgb(throughput, throughput_factor);
	}
	return (throughput);
}

// Since we chose randomly between diffuse and specular,
// we need to account for the times we didn't do one or the other.
t_rgb	rt_account_probability(t_rgb throughput, float ray_probability)
{
	return (rt_scale(throughput, 1.0f / ray_probability));
}
