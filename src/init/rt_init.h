/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_init.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 14:20:13 by sbos          #+#    #+#                 */
/*   Updated: 2023/01/24 14:20:13 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_INIT_H
# define RT_INIT_H

void		rt_assign_capitalized_objects(t_data *data);

t_status	rt_init(int argc, char *argv[], t_data *data);

#endif
