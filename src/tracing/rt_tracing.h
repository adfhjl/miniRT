/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_tracing.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/17 19:22:19 by sbos          #+#    #+#                 */
/*   Updated: 2023/02/23 16:58:11 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_TRACING_H
# define RT_TRACING_H

float		rt_get_ray_action(float *do_specular, float *do_refraction,
				float specular_chance, float refraction_chance);

t_vector	rt_get_refraction_ray_dir(t_hit_info info, t_ray ray,
				float *do_specular, float *do_refraction);
void		rt_get_diffuse_and_specular_ray_dir(t_vector *diffuse_ray_dir,
				t_vector *specular_ray_dir, t_hit_info info, t_ray ray);

t_rgb		rt_absorb(t_hit_info info, t_rgb throughput);
t_rgb		rt_update_throughput(float do_refraction, t_rgb rgb,
				float do_specular, t_rgb throughput);
t_rgb		rt_account_probability(t_rgb throughput, float ray_probability);

t_rgb		rt_trace(t_ray ray, t_data *data);

void		rt_update_specular_and_refraction_chances(float *specular_chance,
				float *refraction_chance, t_ray ray, t_hit_info info);

void		rt_update_ray_dir(t_ray *ray, t_hit_info info, float do_specular,
				float do_refraction);
void		rt_update_ray_pos(t_ray *ray, t_hit_info info, float do_refraction);

#endif
