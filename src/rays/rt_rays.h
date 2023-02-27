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

# include "minirt.h"

t_rgb			rt_get_ray_rgb(t_ray ray, t_data *data);

#endif
