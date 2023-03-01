/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rt_structs.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/17 15:03:49 by sbos          #+#    #+#                 */
/*   Updated: 2023/02/22 17:23:34 by vbenneko      ########   odam.nl         */
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
	t_vector	pos;
	t_vector	dir;
};

struct s_object
{
	float			ratio;
	t_vector		pos;
	t_vector		normal;
	float			fov;
	t_rgb			rgb;
	t_rgb			emissive;
	float			diameter;
	float			height;
	t_object_type	type;
};

struct s_hit_info
{
	float		distance;
	t_vector	surface_normal;
	t_rgb		rgb;
	t_rgb		emissive;
};

struct s_quadratic
{
	bool	solution;
	float	solution_minus;
	float	solution_plus;
}	s_quadratic;

typedef struct s_voronoi_seed
{
	int32_t	x;
	int32_t	y;
}	t_voronoi_seed;

typedef struct s_voronoi
{
	uint32_t		distances[UNSCALED_WINDOW_WIDTH * UNSCALED_WINDOW_HEIGHT];
	t_voronoi_seed	*stack;
	bool			visited[UNSCALED_WINDOW_WIDTH * UNSCALED_WINDOW_HEIGHT];
}	t_voronoi;

struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_object	*objects;

	t_object	*ambient;
	t_object	*camera;
	t_object	*light;

	int			scaled_window_width;
	int			scaled_window_height;
	int			scaled_window_center_x;
	int			scaled_window_center_y;

	bool		moved_cursor;

	float		movement_speed;

	t_voronoi	voronoi;

	size_t		debug_image_index;

	// float		reflection_contribution;

	size_t		samples_since_last_movement;
	float		pixel_channel_floats[UNSCALED_WINDOW_WIDTH * UNSCALED_WINDOW_HEIGHT * 4];

	// TODO: Put in struct
	bool		draw_debug;
	bool		frozen;
	int			draw_mode; // Maybe in this struct as well?
	//

	// TODO: Put in struct
	t_vector	world_up;
	t_vector	camera_forward;
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

	uint32_t	available[UNSCALED_WINDOW_WIDTH * UNSCALED_WINDOW_HEIGHT];
	uint32_t	available_inverse[UNSCALED_WINDOW_WIDTH * UNSCALED_WINDOW_HEIGHT];
	float		densities[UNSCALED_WINDOW_WIDTH * UNSCALED_WINDOW_HEIGHT];

	uint32_t	available_count;

	uint32_t	starting_update_radius;

	uint32_t	pixel_index;
	//
};

#endif
