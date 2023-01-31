/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_parse_objects.h                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 15:39:07 by sbos          #+#    #+#                 */
/*   Updated: 2023/01/24 15:39:07 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_PARSE_OBJECTS_H
# define RT_PARSE_OBJECTS_H

# include "minirt.h"

t_status	rt_parse_ambient(char **line_ptr, t_object *object);
t_status	rt_parse_camera(char **line_ptr, t_object *object);
t_status	rt_parse_cylinder(char **line_ptr, t_object *object);
t_status	rt_parse_light(char **line_ptr, t_object *object);
t_status	rt_parse_plane(char **line_ptr, t_object *object);
t_status	rt_parse_sphere(char **line_ptr, t_object *object);

t_status	rt_check_separating_whitespace(char **line_ptr);

#endif
