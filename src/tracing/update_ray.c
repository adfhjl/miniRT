/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update_ray.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/16 18:53:43 by sbos          #+#    #+#                 */
/*   Updated: 2023/03/16 18:53:43 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rt_structs.h"

#include "rgb/rt_rgb.h"
#include "tracing/rt_tracing.h"
#include "vectors/rt_vectors.h"

#include "debug/rt_debug.h" // TODO: REMOVE

void	rt_update_ray_dir(t_ray *ray, t_hit_info info, float do_specular,
			float do_refraction)
{
	t_vector	diffuse_ray_dir;
	t_vector	specular_ray_dir;
	t_vector	refraction_ray_dir;

	rt_get_diffuse_and_specular_ray_dir(&diffuse_ray_dir, &specular_ray_dir,
		info, *ray);
	refraction_ray_dir = rt_get_refraction_ray_dir(info, *ray, &do_specular,
			&do_refraction);
	ray->dir = rt_mix(diffuse_ray_dir, specular_ray_dir, do_specular);
	rt_assert_normal(ray->dir, "h");
	ray->dir = rt_mix(ray->dir, refraction_ray_dir, do_refraction);
	rt_assert_normal(ray->dir, "i");
}

void	rt_update_ray_pos(t_ray *ray, t_hit_info info, float do_refraction)
{
	float	nudge;

	ray->pos = rt_add(ray->pos, rt_scale(ray->dir, info.distance));
	nudge = SURFACE_NORMAL_NUDGE;
	if (do_refraction == 1.0f)
		nudge *= -1;
	ray->pos = rt_add(ray->pos, rt_scale(info.surface_normal, nudge));
}
