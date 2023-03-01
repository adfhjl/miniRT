/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_get_structs.h                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/24 21:25:16 by sbos          #+#    #+#                 */
/*   Updated: 2023/02/24 21:25:16 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_GET_STRUCTS_H
# define RT_GET_STRUCTS_H

# include "minirt.h"

t_rgb		rt_get_rgb(float r, float g, float b);

t_ray		rt_get_ray(t_vector pos, t_vector normal);

t_vector	rt_get_vector(float x, float y, float z);

#endif
