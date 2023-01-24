/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_field.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 14:32:40 by sbos          #+#    #+#                 */
/*   Updated: 2023/01/24 14:32:40 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "init/parse/rt_parse.h"

t_status	rt_parse_field(char *token, t_object *object,
				t_parsing_state *state)
{
	// TODO: Enforce the float and char ranges in the way the subject PDF states
	if (object->type == OBJECT_TYPE_AMBIENT)
	{
		if (*state == PARSING_STATE_TYPE)
		{
			*state = PARSING_STATE_RATIO;
			if (rt_parse_float(&token, &object->ambient.ratio) == ERROR)
				return (ERROR);
		}
		else if (*state == PARSING_STATE_RATIO)
		{
			*state = PARSING_STATE_END;
			if (rt_parse_rgb(token, &object->ambient.rgb) == ERROR)
				return (ERROR);
		}
	}
	else if (object->type == OBJECT_TYPE_CAMERA)
	{
		if (*state == PARSING_STATE_TYPE)
		{
			*state = PARSING_STATE_COORDINATES;
			if (rt_parse_vector(token, &object->camera.coordinates) == ERROR)
				return (ERROR);
		}
		else if (*state == PARSING_STATE_COORDINATES)
		{
			*state = PARSING_STATE_ORIENTATION;
			if (rt_parse_vector(token, &object->camera.orientation) == ERROR)
				return (ERROR);
		}
		else if (*state == PARSING_STATE_ORIENTATION)
		{
			*state = PARSING_STATE_END;
			// TODO: Maybe also use rt_parse_float() here?
			if (rt_parse_char(&token, &object->camera.fov) == ERROR)
				return (ERROR);
		}
	}
	else if (object->type == OBJECT_TYPE_LIGHT)
	{
		if (*state == PARSING_STATE_TYPE)
		{
			*state = PARSING_STATE_COORDINATES;
			if (rt_parse_vector(token, &object->light.coordinates) == ERROR)
				return (ERROR);
		}
		else if (*state == PARSING_STATE_COORDINATES)
		{
			*state = PARSING_STATE_END;
			if (rt_parse_float(&token, &object->light.brightness) == ERROR)
				return (ERROR);
		}
	}
	else if (object->type == OBJECT_TYPE_SPHERE)
	{
		if (*state == PARSING_STATE_TYPE)
		{
			*state = PARSING_STATE_COORDINATES;
			if (rt_parse_vector(token, &object->sphere.center) == ERROR)
				return (ERROR);
		}
		else if (*state == PARSING_STATE_COORDINATES)
		{
			*state = PARSING_STATE_DIAMETER;
			if (rt_parse_float(&token, &object->sphere.diameter) == ERROR)
				return (ERROR);
		}
		else if (*state == PARSING_STATE_DIAMETER)
		{
			*state = PARSING_STATE_END;
			if (rt_parse_rgb(token, &object->sphere.rgb) == ERROR)
				return (ERROR);
		}
	}
	else if (object->type == OBJECT_TYPE_PLANE)
	{
		if (*state == PARSING_STATE_TYPE)
		{
			*state = PARSING_STATE_COORDINATES;
			if (rt_parse_vector(token, &object->plane.coordinates) == ERROR)
				return (ERROR);
		}
		else if (*state == PARSING_STATE_COORDINATES)
		{
			*state = PARSING_STATE_ORIENTATION;
			if (rt_parse_vector(token, &object->plane.orientation) == ERROR)
				return (ERROR);
		}
		else if (*state == PARSING_STATE_ORIENTATION)
		{
			*state = PARSING_STATE_END;
			if (rt_parse_rgb(token, &object->plane.rgb) == ERROR)
				return (ERROR);
		}
	}
	else if (object->type == OBJECT_TYPE_CYLINDER)
	{
		if (*state == PARSING_STATE_TYPE)
		{
			*state = PARSING_STATE_COORDINATES;
			if (rt_parse_vector(token, &object->cylinder.coordinates) == ERROR)
				return (ERROR);
		}
		else if (*state == PARSING_STATE_COORDINATES)
		{
			*state = PARSING_STATE_ORIENTATION;
			if (rt_parse_vector(token, &object->cylinder.orientation) == ERROR)
				return (ERROR);
		}
		else if (*state == PARSING_STATE_ORIENTATION)
		{
			*state = PARSING_STATE_DIAMETER;
			if (rt_parse_float(&token, &object->cylinder.diameter) == ERROR)
				return (ERROR);
		}
		else if (*state == PARSING_STATE_DIAMETER)
		{
			*state = PARSING_STATE_HEIGHT;
			if (rt_parse_float(&token, &object->cylinder.height) == ERROR)
				return (ERROR);
		}
		else if (*state == PARSING_STATE_HEIGHT)
		{
			*state = PARSING_STATE_END;
			if (rt_parse_rgb(token, &object->cylinder.rgb) == ERROR)
				return (ERROR);
		}
	}
	else
		return (rt_print_error(ERROR_UNREACHABLE));

	return (OK);
}
