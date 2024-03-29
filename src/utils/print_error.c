/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_error.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/17 15:13:35 by sbos          #+#    #+#                 */
/*   Updated: 2023/01/17 15:13:35 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft/src/error/ft_error.h"
#include "libft/src/print/ft_print.h"

#include "rt_enums.h"

#include <unistd.h>

t_status	rt_print_error(t_error ph_error)
{
	static char	*error_messages[] = {
	[ERROR_SYSTEM] = "System error",
	[ERROR_INVALID_ARGC] = "Invalid argument count",
	[ERROR_INVALID_SCENE_NAME] = "Invalid scene name",
	[ERROR_CANT_READ_SCENE_FILE] = "Can't read the scene file",
	[ERROR_NON_OBJECT_TYPE_START]
		= "A scene line started with a non-object type",
	[ERROR_EXPECTED_COMMA] = "Expected a comma",
	[ERROR_UNEXPECTED_COMMA] = "Encountered an unexpected comma",
	[ERROR_FAILED_TO_PARSE_FLOAT] = "Failed to parse a float",
	[ERROR_FLOAT_OUT_OF_RANGE] = "Encountered a float that was too big/small",
	[ERROR_UNEXPECTED_EXTRA_FIELD] = "Encountered an unexpected extra field",
	[ERROR_WRONG_CAPITALIZED_OBJECT_COUNT]
		= "Wrong capitalized object count",
	[ERROR_EXPECTED_WHITESPACE] = "Expected whitespace",
	[ERROR_INVALID_CAMERA_DIR] = "Invalid x=0, z=0 camera direction",
	[ERROR_INVALID_ZERO_NORMAL] = "Invalid x=0, y=0, z=0 normal",
	[ERROR_MLX] = "MLX error",
	};
	char		*error_message;

	error_message = error_messages[ph_error];
	ft_putendl_fd("Error", STDERR_FILENO);
	ft_putendl_fd(error_message, STDERR_FILENO);
	return (ERROR);
}
