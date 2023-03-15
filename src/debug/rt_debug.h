/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_debug.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/20 17:06:56 by sbos          #+#    #+#                 */
/*   Updated: 2023/01/20 17:06:56 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_DEBUG_H
# define RT_DEBUG_H

t_status	rt_draw_debug_lines(t_data *data);

void	rt_print_scene(t_data *data);

// TODO: REMOVE THIS BEFORE HANDING IN!!!
void	rt_assert_normal(t_vector vector, char *location);

#endif
