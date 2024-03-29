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

# include "rt_structs.h"

t_status	rt_draw_debug_lines(t_data *data);

t_vector	rt_get_ray_endpoint(t_ray ray, float t);

t_ray		rt_get_ray(t_vector pos, t_vector normal);

float		rt_lerp(float old, float new_, float t);

float		rt_max(float a, float b);

t_status	rt_print_error(t_error ph_error);

void		rt_shuffle(uint32_t *arr, size_t length);
float		rt_random_float_01(void);

t_quadratic	rt_solve_quadratic(float a, float b, float c);

#endif
