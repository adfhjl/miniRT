/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   trace.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbenneko <vbenneko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 17:15:53 by vbenneko      #+#    #+#                 */
/*   Updated: 2023/02/23 17:55:58 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft/src/vector/ft_vector.h"

#include "rt_structs.h"

#include "collisions/rt_collisions.h"
#include "rgb/rt_rgb.h"
#include "tracing/rt_tracing.h"
#include "utils/rt_utils.h"
#include "vectors/rt_vectors.h"

#include <math.h>

static t_rgb	rt_apply_ambient(t_rgb rgb, t_object *ambient,
					t_vector throughput)
{
	t_rgb	ambient_rgb;

	ambient_rgb = rt_scale(ambient->material.rgb, ambient->ratio);
	return (rt_add(rgb, rt_multiply_rgb(ambient_rgb, throughput)));
}

static bool	rt_russian_roulette(t_vector *throughput)
{
	float	p;

	p = rt_max(throughput->r, rt_max(throughput->g, throughput->b));
	if (rt_random_float_01() > p)
		return (true);
	*throughput = rt_scale(*throughput, 1.0f / p);
	return (false);
}

static t_hit_info	rt_get_hit_info(t_ray ray, t_data *data)
{
	t_hit_info	info;
	size_t		i;

	info.distance = INFINITY;
	i = 0;
	while (i < ft_vector_get_size(data->objects))
	{
		if (data->objects[i].type == OBJECT_TYPE_PLANE)
			rt_get_plane_collision_info(ray, data->objects[i], &info);
		else if (data->objects[i].type == OBJECT_TYPE_SPHERE
			|| data->objects[i].type == OBJECT_TYPE_LIGHT)
			rt_get_sphere_collision_info(ray, data->objects[i], &info);
		else if (data->objects[i].type == OBJECT_TYPE_CYLINDER)
			rt_get_cylinder_collision_info(ray, data->objects[i], &info);
		i++;
	}
	return (info);
}

static bool	rt_bounce(t_bouncing *b, t_data *data)
{
	b->info = rt_get_hit_info(b->ray, data);
	if (b->info.distance == INFINITY)
	{
		b->rgb = rt_add(b->rgb, rt_multiply_rgb(b->background, b->throughput));
		return (true);
	}
	if (b->info.inside)
		b->throughput = rt_absorb(b->info, b->throughput);
	rt_update_specular_and_refraction_chances(&b->specular_chance,
		&b->refraction_chance, b->ray, b->info);
	b->ray_probability = rt_get_ray_action(&b->do_specular,
			&b->do_refraction, b->specular_chance, b->refraction_chance);
	rt_update_ray_pos(&b->ray, b->info, b->do_refraction);
	rt_update_ray_dir(&b->ray, b->info, b->do_specular, b->do_refraction);
	b->rgb = rt_add(b->rgb, rt_multiply_rgb(b->info.material.emissive,
				b->throughput));
	b->throughput = rt_update_throughput(b->do_refraction, b->info.material.rgb,
			b->do_specular, b->throughput);
	b->throughput = rt_account_probability(b->throughput, b->ray_probability);
	if (rt_russian_roulette(&b->throughput))
		return (true);
	b->rgb = rt_apply_ambient(b->rgb, data->ambient, b->throughput);
	return (false);
}

t_rgb	rt_trace(t_ray ray, t_data *data)
{
	t_bouncing	b;
	size_t		bounce_index;

	b.ray = ray;
	b.rgb = (t_rgb){0, 0, 0};
	b.throughput = (t_rgb){1, 1, 1};
	b.background = rt_srgb_to_linear(
			(t_rgb){BACKGROUND_R, BACKGROUND_G, BACKGROUND_B});
	bounce_index = 0;
	while (bounce_index <= MAX_BOUNCES_PER_RAY)
	{
		if (rt_bounce(&b, data))
			break ;
		bounce_index++;
	}
	return (b.rgb);
}
