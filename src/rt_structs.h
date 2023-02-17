/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_structs.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/17 15:03:49 by sbos          #+#    #+#                 */
/*   Updated: 2023/02/17 15:03:49 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_STRUCTS_H
# define RT_STRUCTS_H

struct s_rgb
{
	float	r;
	float	g;
	float	b;
};

struct s_vector
{
	float	x;
	float	y;
	float	z;
};

struct s_ray
{
	t_vector	origin;
	t_vector	normal;
};

struct s_ambient
{
	float	ratio;
	t_rgb	rgb;
};

struct s_camera
{
	t_vector	origin;
	t_vector	normal;
	float		fov;
};

struct s_light
{
	t_vector	origin;
	float		brightness;
	t_rgb		rgb;
};

struct s_sphere
{
	t_vector	origin;
	float		diameter;
	t_rgb		rgb;
};

struct s_plane
{
	t_vector	origin;
	t_vector	normal;
	t_rgb		rgb;
};

struct s_cylinder
{
	t_vector	origin;
	t_vector	normal;
	float		diameter;
	float		height;
	t_rgb		rgb;
};

struct s_object
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
};

struct s_hit_info
{
	t_object		*object;
	float			distance;
	t_vector		surface_normal;
	t_visibility	visibility;
};

struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_object	*objects;
	t_ambient	*ambient;
	t_camera	*camera;
	t_light		*light;

	bool		draw_debug;

	int			window_center_x;
	int			window_center_y;
	bool		moved_cursor;

	// TODO: Put in struct
	t_vector	world_up;
	t_vector	camera_right;
	t_vector	camera_up;
	float		dist_per_pix;
	t_vector	canvas_top_left;
	//

	// TODO: Put in struct
	bool		w_held;
	bool		a_held;
	bool		s_held;
	bool		d_held;
	bool		space_held;
	bool		shift_held;
	//

	// TODO: Put in struct
	uint32_t	pixel_count;

	uint32_t	available[WINDOW_WIDTH * WINDOW_HEIGHT];
	uint32_t	available_inverse[WINDOW_WIDTH * WINDOW_HEIGHT];
	float		densities[WINDOW_WIDTH * WINDOW_HEIGHT];

	uint32_t	available_count;

	float		starting_update_radius;

	uint32_t	pixel_index;
	//
};

#endif
