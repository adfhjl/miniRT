/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_collisions.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/17 14:55:28 by sbos          #+#    #+#                 */
/*   Updated: 2023/02/22 17:18:53 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_COLLISIONS_H
# define RT_COLLISIONS_H

t_hit_info	rt_get_cylinder_collision_info(t_ray ray, t_object cylinder);

t_rgb		rt_get_line_rgb(t_ray ray, t_hit_info info, t_object object);

t_hit_info	rt_get_plane_collision_info(t_ray ray, t_object plane);

t_hit_info	rt_get_sphere_collision_info(t_ray ray, t_object sphere);

#endif
