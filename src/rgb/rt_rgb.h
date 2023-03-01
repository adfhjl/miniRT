/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_rgb.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/01 19:17:04 by sbos          #+#    #+#                 */
/*   Updated: 2023/03/01 19:17:04 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_RGB_H
# define RT_RGB_H

# include "minirt.h"

t_rgb	rt_add_rgb(t_rgb a, t_rgb b);

t_rgb	rt_multiply_rgb(t_rgb a, t_rgb b);

t_rgb	rt_scale_rgb(t_rgb v, float f);

#endif
