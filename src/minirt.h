/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbenneko <vbenneko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/16 17:28:47 by vbenneko      #+#    #+#                 */
/*   Updated: 2023/01/16 17:29:10 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "MLX42/MLX42.h"

# include "rt_enums.h"
# include "utils/rt_utils.h"

# define WINDOW_TITLE "miniRT"
# define SYSTEM_ERROR_STATUS -1

typedef struct s_rgb
{
	float	r;
	float	g;
	float	b;
}	t_rgb;

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}	t_vector;

typedef struct s_ambient
{
	float	ratio;
	t_rgb	rgb;
}	t_ambient;

typedef struct s_camera
{
	t_vector	coordinates;
	t_vector	orientation;
	float		fov;
}	t_camera;

typedef struct s_light
{
	t_vector	coordinates;
	float		brightness;
}	t_light;

typedef struct s_sphere
{
	t_vector	center;
	float		diameter;
	t_rgb		rgb;
}	t_sphere;

typedef struct s_plane
{
	t_vector	coordinates;
	t_vector	orientation;
	t_rgb		rgb;
}	t_plane;

typedef struct s_cylinder
{
	t_vector	coordinates;
	t_vector	orientation;
	float		diameter;
	float		height;
	t_rgb		rgb;
}	t_cylinder;

typedef struct s_object
{
	union
	{
		t_ambient	ambient;
		t_camera	camera;
		t_light		light;
		t_sphere	sphere;
		t_plane		plane;
		t_cylinder	cylinder;
	};
	t_object_type	type;
}	t_object;

typedef struct s_data
{
	mlx_t		*mlx;
	char		*scene_path;
	t_object	*objects;
	t_ambient	*ambient;
	t_camera	*camera;
	t_light		*light;
}	t_data;

typedef t_status	(*t_parse_fn)(char **line_ptr, t_object *object);

#endif
