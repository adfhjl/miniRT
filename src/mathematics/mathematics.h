/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mathematics.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbenneko <vbenneko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 16:31:04 by vbenneko      #+#    #+#                 */
/*   Updated: 2023/02/01 17:18:56 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHEMATICS_H
# define MATHEMATICS_H

# include "minirt.h"

typedef struct s_vector	t_vector;
typedef struct s_rgb	t_rgb;
typedef struct s_ray	t_ray;
typedef struct s_data	t_data;

//
// rt_get_ray_rgb.c

t_rgb		rt_get_ray_rgb(t_ray ray, t_data *data);

//
// utils/*

t_vector	rt_add(t_vector a, t_vector b);
t_vector	rt_cross(t_vector a, t_vector b);
float		rt_dot(t_vector a, t_vector b);
t_vector	rt_get_ray_point(t_ray ray, float t);
float		rt_mag(t_vector v);
float		rt_mag2(t_vector v);
t_rgb		rt_multiply_rgb(t_rgb a, t_rgb b);
t_vector	rt_normalized(t_vector v);
t_vector	rt_scale(t_vector v, float f);
t_rgb		rt_scale_rgb(t_rgb v, float f);
t_vector	rt_sub(t_vector a, t_vector b);

#endif
