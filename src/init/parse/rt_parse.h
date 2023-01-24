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

t_status	rt_parse_argv(char *argv[], t_data *data);

t_status	rt_parse_char(char **token_ptr, unsigned char *field_ptr);

t_status	rt_parse_field(char *token, t_object *object,
				t_parsing_state *state);

t_status	rt_parse_float(char **token_ptr, float *field_ptr);

t_status	rt_parse_object(char *line, t_object *object);

t_status	rt_parse_rgb(char *token, t_rgb *rgb);

char		*rt_parse_token(char **line_ptr);

t_status	rt_parse_vector(char *token, t_vector *vector);

t_status	rt_skip_separator_comma(char **token_ptr);

#endif
