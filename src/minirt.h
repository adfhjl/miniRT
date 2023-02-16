/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbenneko <vbenneko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/16 17:28:47 by vbenneko      #+#    #+#                 */
/*   Updated: 2023/02/10 18:38:27 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "MLX42/MLX42.h"

# include "rt_enums.h"
# include "utils/rt_utils.h"
# include "mathematics/mathematics.h"

# include <math.h>

# include <assert.h> // TODO: Remove before handing the project in

# define WINDOW_TITLE "miniRT"
# define SYSTEM_ERROR_STATUS -1
# define WINDOW_WIDTH 500
# define WINDOW_HEIGHT 500

# define BACKGROUND_R (uint32_t)128
# define BACKGROUND_G (uint32_t)128
# define BACKGROUND_B (uint32_t)128

# define UNRENDERED_R (uint32_t)42
# define UNRENDERED_G (uint32_t)42
# define UNRENDERED_B (uint32_t)42

// # define BACKGROUND_R 255
// # define BACKGROUND_G 255
// # define BACKGROUND_B 255

# define EPSILON 1e-4
# define LIGHT_BRIGHTNESS_FACTOR 100.f
# define MOVEMENT_STEP_SIZE 0.1f
# define ROTATION_FACTOR 0.005
# define RAYS_SHOT_PER_FRAME 2000

# define DEBUG_DRAWING_DEPTH 1
# define DEBUG_DRAWING_ON_BY_DEFAULT true

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

typedef struct s_ray
{
	t_vector	origin;
	t_vector	normal;
}	t_ray;

typedef struct s_ambient
{
	float	ratio;
	t_rgb	rgb;
}	t_ambient;

typedef struct s_camera
{
	t_vector	origin;
	t_vector	normal;
	float		fov;
}	t_camera;

typedef struct s_light
{
	t_vector	origin;
	float		brightness;
	t_rgb		rgb;
}	t_light;

typedef struct s_sphere
{
	t_vector	origin;
	float		diameter;
	t_rgb		rgb;
}	t_sphere;

typedef struct s_plane
{
	t_vector	origin;
	t_vector	normal;
	t_rgb		rgb;
}	t_plane;

typedef struct s_cylinder
{
	t_vector	origin;
	t_vector	normal;
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

typedef struct s_hit_info
{
	t_object		*object;
	float			distance;
	t_vector		surface_normal;
	t_visibility	visibility;
}	t_hit_info;

typedef struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_object	*objects;
	t_ambient	*ambient;
	t_camera	*camera;
	t_light		*light;

	t_vector	world_up;
	t_vector	camera_right;
	t_vector	camera_up;
	float		dist_per_pix;
	t_vector	canvas_top_left;

	bool		w_held;
	bool		a_held;
	bool		s_held;
	bool		d_held;
	bool		space_held;
	bool		shift_held;

	bool		draw_debug;

	int			window_center_x;
	int			window_center_y;

	uint32_t	pixel_lookup_indices[WINDOW_WIDTH * WINDOW_HEIGHT];
	uint32_t	pixel_lookup_index;
}	t_data;

typedef t_status	(*t_parse_fn)(char **line_ptr, t_object *object);

#endif
