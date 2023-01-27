/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_parse.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 14:28:42 by sbos          #+#    #+#                 */
/*   Updated: 2023/01/24 14:28:42 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_PARSE_H
# define RT_PARSE_H

# include "minirt.h"

t_status	rt_parse_argv(char *argv[], t_data *data, char *buf);

t_status	rt_parse_float(char **line_ptr, float *field_ptr);
t_status	rt_parse_object(char *line, t_object *object);
t_status	rt_parse_range_float(char **line_ptr, float *field_ptr,
				float start, float end);
t_status	rt_parse_rgb(char **line_ptr, t_rgb *rgb);
t_status	rt_parse_vector(char **line_ptr, t_vector *vector);

t_status	rt_skip_separator_comma(char **line_ptr);
void		rt_skip_whitespace(char **line_ptr);

#endif
