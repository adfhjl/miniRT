/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_rays.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/17 19:22:19 by sbos          #+#    #+#                 */
/*   Updated: 2023/02/23 16:58:11 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_RAYS_H
# define RT_RAYS_H

t_rgb			rt_get_point_rgb(t_ray ray, t_hit_info info, t_data *data,
					t_rgb object_color);

t_hit_info		rt_get_hit_info(t_ray ray, t_data *data);
t_rgb			rt_get_ray_rgb(t_ray ray, t_data *data, int depth);

t_ray			rt_get_ray(t_vector origin, t_vector normal);

#endif
