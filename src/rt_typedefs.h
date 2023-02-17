/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_typedefs.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/17 14:59:47 by sbos          #+#    #+#                 */
/*   Updated: 2023/02/17 14:59:47 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_TYPEDEFS_H
# define RT_TYPEDEFS_H

typedef struct s_rgb		t_rgb;
typedef struct s_vector		t_vector;
typedef struct s_ray		t_ray;
typedef struct s_ambient	t_ambient;
typedef struct s_camera		t_camera;
typedef struct s_light		t_light;
typedef struct s_sphere		t_sphere;
typedef struct s_plane		t_plane;
typedef struct s_cylinder	t_cylinder;
typedef struct s_object		t_object;
typedef struct s_hit_info	t_hit_info;
typedef struct s_data		t_data;

typedef t_status			(*t_parse_fn)(char **line_ptr, t_object *object);

#endif
