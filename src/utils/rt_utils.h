/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_utils.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/19 17:42:22 by sbos          #+#    #+#                 */
/*   Updated: 2023/01/19 17:42:22 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_UTILS_H
# define RT_UTILS_H

# include "minirt.h"

t_status	rt_print_error(t_error ph_error);

void		rt_shuffle(uint32_t *arr, size_t length);
float		rt_random_float_01(void);

#endif
