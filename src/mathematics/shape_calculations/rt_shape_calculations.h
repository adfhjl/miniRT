/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_shape_calculations.h                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/17 14:55:28 by sbos          #+#    #+#                 */
/*   Updated: 2023/02/17 14:55:28 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_SHAPE_CALCULATIONS_H
# define RT_SHAPE_CALCULATIONS_H

# include "minirt.h"

t_hit_info	rt_get_cylinder_collision_info(
				t_ray ray, t_object *object, t_data *data);

t_hit_info	rt_get_sphere_collision_info(
				t_ray ray, t_object *object, t_data *data);

t_hit_info	rt_get_plane_collision_info(
				t_ray ray, t_object *object, t_data *data);

#endif
