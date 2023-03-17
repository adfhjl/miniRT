/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_print.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 19:04:28 by sbos          #+#    #+#                 */
/*   Updated: 2023/03/17 19:04:28 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_PRINT_H
# define RT_PRINT_H

void	rt_print_rgb(t_rgb rgb);

void	rt_print_scene(t_data *data);

void	rt_print_vector(t_vector v);

void	rt_try_print_rgb(t_object object);
void	rt_try_print_diameter(t_object object);
void	rt_try_print_normal(t_object object);
void	rt_try_print_ratio(t_object object);
void	rt_try_print_pos(t_object object);

void	rt_try_print_height(t_object object);
void	rt_try_print_fov(t_object object);

#endif
