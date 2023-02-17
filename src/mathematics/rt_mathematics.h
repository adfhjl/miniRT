/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_mathematics.h                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbenneko <vbenneko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 16:31:04 by vbenneko      #+#    #+#                 */
/*   Updated: 2023/02/14 14:09:43 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_MATHEMATICS_H
# define RT_MATHEMATICS_H

# include "minirt.h"

t_rgb			rt_get_point_rgb(t_ray ray, t_hit_info info, t_data *data,
					t_rgb object_color);

t_visibility	rt_get_visibility(t_hit_info info, t_ray camera_ray,
					t_light *light);
t_hit_info		rt_get_hit_info(t_ray ray, t_data *data);
t_rgb			rt_get_ray_rgb(t_ray ray, t_data *data);

t_ray			rt_get_ray(t_vector origin, t_vector normal);

#endif
