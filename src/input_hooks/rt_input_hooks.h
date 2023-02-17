/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_input_hooks.h                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/17 14:51:02 by sbos          #+#    #+#                 */
/*   Updated: 2023/02/17 14:51:02 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_INPUT_HOOKS_H
# define RT_INPUT_HOOKS_H

void	rt_key_hook(mlx_key_data_t keydata, void *param);
void	rt_cursor_hook(double xpos, double ypos, void* param);

#endif
