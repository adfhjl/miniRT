/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_enums.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/19 18:11:17 by sbos          #+#    #+#                 */
/*   Updated: 2023/01/19 18:11:17 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_ENUMS_H
# define RT_ENUMS_H

typedef enum e_error
{
	ERROR_SYSTEM,
	ERROR_INVALID_ARGC,
	ERROR_INVALID_SCENE_NAME,
	ERROR_CANT_READ_SCENE_FILE,
}	t_error;

#endif
