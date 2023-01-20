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

// TODO: Just before the eval, make sure every enum
// has a corresponding string in print_error()
typedef enum e_error
{
	ERROR_SYSTEM,
	ERROR_INVALID_ARGC,
	ERROR_INVALID_SCENE_NAME,
	ERROR_CANT_READ_SCENE_FILE,
	ERROR_NON_OBJECT_TYPE_START,
	ERROR_UNREACHABLE,
	ERROR_EXPECTED_COMMA,
	ERROR_UNEXPECTED_COMMA,
	ERROR_FAILED_TO_PARSE_CHAR,
	ERROR_FAILED_TO_PARSE_FLOAT,
	ERROR_UNEXPECTED_EXTRA_FIELD,
}	t_error;

typedef enum e_object_type
{
	OBJECT_TYPE_NONE,
	OBJECT_TYPE_AMBIENT,
	OBJECT_TYPE_CAMERA,
	OBJECT_TYPE_LIGHT,
	OBJECT_TYPE_SPHERE,
	OBJECT_TYPE_PLANE,
	OBJECT_TYPE_CYLINDER,
}	t_object_type;

typedef enum e_parsing_state
{
	PARSING_STATE_TYPE,
	PARSING_STATE_END,
	PARSING_STATE_RATIO,
	PARSING_STATE_COORDINATES,
	PARSING_STATE_ORIENTATION,
	PARSING_STATE_DIAMETER,
	PARSING_STATE_HEIGHT,
}	t_parsing_state;

#endif
