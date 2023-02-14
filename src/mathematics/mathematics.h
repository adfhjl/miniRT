/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mathematics.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbenneko <vbenneko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 16:31:04 by vbenneko      #+#    #+#                 */
/*   Updated: 2023/02/14 14:09:43 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHEMATICS_H
# define MATHEMATICS_H

# include "minirt.h"

typedef struct s_vector		t_vector;
typedef struct s_rgb		t_rgb;
typedef struct s_ray		t_ray;
typedef struct s_data		t_data;
typedef struct s_hit_info	t_hit_info;
typedef struct s_object		t_object;
typedef struct s_light		t_light;

//
// shape_calculations/*

t_hit_info	rt_get_cylinder_collision_info(
				t_ray ray, t_object *object, t_data *data);

t_hit_info	rt_get_sphere_collision_info(
				t_ray ray, t_object *object, t_data *data);

t_hit_info	rt_get_plane_collision_info(
				t_ray ray, t_object *object, t_data *data);

//
// rt_get_point_rgb.c

t_rgb		rt_get_point_rgb(t_ray ray, t_hit_info info, t_data *data,
				t_rgb object_color);

//
// rt_get_ray_rgb.c

t_visibility	rt_get_visibility(t_hit_info info, t_ray camera_ray,
				t_light *light);
t_hit_info	rt_get_hit_info(t_ray ray, t_data *data);
t_rgb		rt_get_ray_rgb(t_ray ray, t_data *data);

t_ray		rt_get_ray(t_vector origin, t_vector normal);

//
// utils/*

t_vector	rt_add(t_vector a, t_vector b);
t_rgb		rt_add_rgb(t_rgb a, t_rgb b);
t_vector	rt_cross(t_vector a, t_vector b);
float		rt_dot(t_vector a, t_vector b);
t_vector	rt_get_ray_point(t_ray ray, float t);
float		rt_mag(t_vector v);
t_rgb		rt_multiply_rgb(t_rgb a, t_rgb b);
t_vector	rt_normalized(t_vector v);
t_vector	rt_scale(t_vector v, float f);
t_rgb		rt_scale_rgb(t_rgb v, float f);
t_vector	rt_sub(t_vector a, t_vector b);

#endif
