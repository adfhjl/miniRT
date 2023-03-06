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

typedef struct s_vector		t_rgb;
typedef struct s_vector		t_vector;
typedef struct s_ray		t_ray;
typedef struct s_object		t_object;
typedef struct s_hit_info	t_hit_info;
typedef struct s_quadratic	t_quadratic;
typedef struct s_data		t_data;

typedef t_status			(*t_parse_fn)(char **line_ptr, t_object *object);

#endif
