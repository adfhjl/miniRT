/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/24 14:21:07 by sbos          #+#    #+#                 */
/*   Updated: 2023/02/10 15:07:59 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "init/parse/rt_parse.h"
#include "debug/rt_debug.h"

// forward = (0, 0, 1);
//
// leftmost = (sin(-35o), 0, cos(-35o))
// rightmost = (sin(35o), 0, cos(35o))
// leftmost.xyz /= leftmost.z;
// rightmost.xyz /= rightmost.z;
//
// leftmost = (sin(-35o) / cos(-35o), 0 / cos(-35o), cos(-35o) / cos(-35o))
// rightmost = (sin(35o) / cos(35o), 0 / cos(35o), cos(35o) /cos(35o))
//
// leftmost = (-sin(35o) / cos(35o), 0, 1)
// rightmost = (sin(35o) / cos(35o), 0, 1)
//
// leftmost = (-tan(35o), 0, 1)
// rightmost = (tan(35o), 0, 1)
//
// width = abs(leftmost.x - rightmost.x);
//
// width = abs(-tan(35o) - tan(35o));
//
// tan(0) is 0, tan() until 90 degrees is positive, 90 is NAN (+-inf)
// width = abs(-2 * tan(35o));
// TODO: Call this every frame
static void	rt_update_canvas_info(t_data *data)
{
	const t_vector camera_forward = data->camera->normal;

	data->camera_right = rt_normalized(rt_cross(camera_forward, data->world_up));
	assert(!isnan(data->camera_right.x) && !isnan(data->camera_right.y) && !isnan(data->camera_right.z));

	data->camera_up = rt_cross(data->camera_right, camera_forward);
	// TODO: If this assert is never ever triggered in any of the scenes, remove it
	assert(!isnan(data->camera_up.x) && !isnan(data->camera_up.y) && !isnan(data->camera_up.z));
	// if (isnan(data->camera_up.x) || isnan(data->camera_up.y) || isnan(data->camera_up.z))
	// 	return (ERROR);

	float half_fov_rad = data->camera->fov / 2 * ((float)M_PI / 180);
	float canvas_width = fabsf(-2 * tanf(half_fov_rad));
	data->dist_per_pix = canvas_width / WINDOW_WIDTH;
	float canvas_height = data->dist_per_pix * WINDOW_HEIGHT;
	t_vector left_canvas_side = rt_add(rt_scale(data->camera_right, -canvas_width / 2), camera_forward);
	t_vector top_canvas_side = rt_add(rt_scale(data->camera_up, canvas_height / 2), camera_forward);
	data->canvas_top_left = rt_add(left_canvas_side, top_canvas_side);
}

static void	rt_clear_image(mlx_image_t *image)
{
	uint32_t	x;
	uint32_t	y;
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			mlx_put_pixel(image, x, y, (UNRENDERED_R << 24) | (UNRENDERED_G << 16) | (UNRENDERED_B << 8) | 0xFF);
			x++;
		}
		y++;
	}
}

static void	rt_reset_canvas_info(t_data *data)
{
	rt_update_canvas_info(data);
	data->pixel_lookup_index = 0;
	rt_clear_image(data->image);
}

static bool	rt_any_movement_key_pressed(t_data *data)
{
	return (data->w_held
		|| data->a_held
		|| data->s_held
		|| data->d_held
		|| data->space_held
		|| data->shift_held);
}

#include <stdio.h> // TODO: REMOVE

static void	rt_key_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;

	if (keydata.action == MLX_RELEASE)
	{
		if (keydata.key == MLX_KEY_W)
			data->w_held = false;
		if (keydata.key == MLX_KEY_A)
			data->a_held = false;
		if (keydata.key == MLX_KEY_S)
			data->s_held = false;
		if (keydata.key == MLX_KEY_D)
			data->d_held = false;
		if (keydata.key == MLX_KEY_SPACE)
			data->space_held = false;
		if (keydata.key == MLX_KEY_LEFT_SHIFT)
			data->shift_held = false;
	}
	else if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(data->mlx);

		if (keydata.key == MLX_KEY_G)
			data->draw_debug = !data->draw_debug;

		if (keydata.key == MLX_KEY_W)
			data->w_held = true;
		if (keydata.key == MLX_KEY_A)
			data->a_held = true;
		if (keydata.key == MLX_KEY_S)
			data->s_held = true;
		if (keydata.key == MLX_KEY_D)
			data->d_held = true;
		if (keydata.key == MLX_KEY_SPACE)
			data->space_held = true;
		if (keydata.key == MLX_KEY_LEFT_SHIFT)
			data->shift_held = true;
	}
}

static char	*rt_get_allocation_count_string(void)
{
	char	*string;
	char	*string_full;

	string = ft_itoa((t_i32)ft_get_allocation_count());
	if (string == NULL)
		return (NULL);
	string_full = ft_strjoin("Allocation count: ", string);
	ft_free(&string);
	return (string_full);
}

#include "../MLX42/src/font/font.h"

static t_status	rt_draw_allocation_count(t_data *data)
{
	static mlx_image_t	*image;
	char				*string;

	if (image != NULL)
		mlx_delete_image(data->mlx, image);
	if (!data->draw_debug)
		return (OK);
	string = rt_get_allocation_count_string();
	if (string == NULL)
		return (ERROR);
	image = mlx_put_string(data->mlx, string, 0, FONT_HEIGHT);
	ft_free(&string);
	if (image == NULL)
		return (rt_print_error(ERROR_MLX));
	mlx_set_instance_depth(&image->instances[0], DEBUG_DRAWING_DEPTH);
	return (OK);
}

static char	*rt_get_fps_string(t_data *data)
{
	char	*string;
	char	*string_full;

	string = ft_itoa((t_i32)(1 / data->mlx->delta_time));
	if (string == NULL)
		return (NULL);
	string_full = ft_strjoin(string, " FPS");
	ft_free(&string);
	return (string_full);
}

static t_status	rt_draw_fps(t_data *data)
{
	static mlx_image_t	*image; // TODO: See if we still want this to be static?
	char				*string;

	if (image != NULL)
		mlx_delete_image(data->mlx, image);
	if (!data->draw_debug)
		return (OK);
	string = rt_get_fps_string(data);
	if (string == NULL)
		return (rt_print_error(ERROR_SYSTEM));
	image = mlx_put_string(data->mlx, string, 0, 0);
	ft_free(&string);
	if (image == NULL)
		return (rt_print_error(ERROR_MLX));
	mlx_set_instance_depth(&image->instances[0], DEBUG_DRAWING_DEPTH);
	return (OK);
}

static uint32_t rt_convert_color(t_rgb rgb)
{
	const uint32_t	r = (uint32_t)(rgb.r * 255);
	const uint32_t	g = (uint32_t)(rgb.g * 255);
	const uint32_t	b = (uint32_t)(rgb.b * 255);

	return ((r << 24) | (g << 16) | (b << 8) | 0xFF);
}

static t_ray	rt_create_ray(uint32_t x, uint32_t y, t_data *data)
{
	t_vector	pixel_ray_x = rt_scale(data->camera_right, x * data->dist_per_pix);
	t_vector	pixel_ray_y = rt_scale(data->camera_up, y * -data->dist_per_pix);
	t_vector	pixel_ray = rt_add(rt_add(data->canvas_top_left, pixel_ray_x), pixel_ray_y);
	t_vector	dir = rt_normalized(pixel_ray);

	return (rt_get_ray(data->camera->origin, dir));
}

// Source: https://stackoverflow.com/a/11946674/13279557
static unsigned int	rt_rand(void)
{
	static unsigned int	seed = 1;

	seed = (seed * 1103515245U + 12345U) & 0x7fffffffU;
	return (seed);
}

static void	rt_draw_loop(void *param)
{
	t_data *const	data = param;
	t_rgb			rgb;
	t_ray			ray;
	uint32_t		y;
	uint32_t		x;

	if (rt_any_movement_key_pressed(data) || data->moved_cursor)
		rt_reset_canvas_info(data);
	data->moved_cursor = false;

	mlx_set_mouse_pos(data->mlx, data->window_center_x, data->window_center_y);

	if (data->w_held)
		data->camera->origin = rt_get_ray_point(rt_get_ray(data->camera->origin, data->camera->normal), MOVEMENT_STEP_SIZE);
	if (data->a_held)
		data->camera->origin = rt_get_ray_point(rt_get_ray(data->camera->origin, data->camera_right), -MOVEMENT_STEP_SIZE);
	if (data->s_held)
		data->camera->origin = rt_get_ray_point(rt_get_ray(data->camera->origin, data->camera->normal), -MOVEMENT_STEP_SIZE);
	if (data->d_held)
		data->camera->origin = rt_get_ray_point(rt_get_ray(data->camera->origin, data->camera_right), MOVEMENT_STEP_SIZE);
	if (data->space_held)
		data->camera->origin = rt_get_ray_point(rt_get_ray(data->camera->origin, data->camera_up), MOVEMENT_STEP_SIZE);
	if (data->shift_held)
		data->camera->origin = rt_get_ray_point(rt_get_ray(data->camera->origin, data->camera_up), -MOVEMENT_STEP_SIZE);

	size_t	ray_loop_index;
	ray_loop_index = 0;
	while (ray_loop_index < RAYS_SHOT_PER_FRAME && data->pixel_lookup_index < WINDOW_WIDTH * WINDOW_HEIGHT)
	{
		uint32_t	index;

		index = data->pixel_lookup_indices[data->pixel_lookup_index];
		x = index % WINDOW_WIDTH;
		y = index / WINDOW_WIDTH;

		ray = rt_create_ray(x, y, data); // TODO: Revamp this function to not recalculate stuff unnecesarally
		rgb = rt_get_ray_rgb(ray, data);
		mlx_put_pixel(data->image, x, y, rt_convert_color(rgb));

		data->pixel_lookup_index++;
		ray_loop_index++;
	}

	if (rt_draw_fps(data) == ERROR || rt_draw_allocation_count(data) == ERROR)
		mlx_close_window(data->mlx);
}

static bool	rt_camera_is_invalid(t_data *data)
{
	const t_vector	camera_forward = data->camera->normal;

	data->world_up = (t_vector){.x = 0.0f, .y = 1.0f, .z = 0.0f};
	data->camera_right = rt_normalized(rt_cross(camera_forward, data->world_up));
	if (isnan(data->camera_right.x) || isnan(data->camera_right.y) || isnan(data->camera_right.z))
		return (true);
	return (data->camera
	&& data->camera->normal.x == 0
	&& data->camera->normal.z == 0);
}

static t_object	*rt_get_object_ptr(t_object_type searched_object_type,
					t_object *objects)
{
	size_t	object_index;
	size_t	size;

	object_index = 0;
	size = ft_vector_get_size(objects);
	while (object_index < size)
	{
		if (objects[object_index].type == searched_object_type)
			return (&objects[object_index]);
		object_index++;
	}
	return (NULL);
}

static void	rt_assign_capitalized_objects(t_data *data)
{
	data->ambient
		= &rt_get_object_ptr(OBJECT_TYPE_AMBIENT, data->objects)->ambient;
	data->camera
		= &rt_get_object_ptr(OBJECT_TYPE_CAMERA, data->objects)->camera;
	data->light
		= &rt_get_object_ptr(OBJECT_TYPE_LIGHT, data->objects)->light;
}

static void rt_cursor_hook(double xpos, double ypos, void* param)
{
	t_data	*data;
	double	dx;
	double	dy;

	data = param;
	// printf("xpos: %f, ypos: %f\n", xpos, ypos);
	dx = xpos - data->window_center_x;
	dy = -(ypos - data->window_center_y);
	// printf("dx: %f, dy: %f\n", dx, dy);

	t_vector	rotation_right;
	rotation_right = rt_scale(data->camera_right, (float)dx * (float)ROTATION_FACTOR);
	// printf("rotation right: x: %f, y: %f, z: %f\n", rotation_right.x, rotation_right.y, rotation_right.z);
	t_vector	rotation_up;
	rotation_up = rt_scale(data->camera_up, (float)dy * (float)ROTATION_FACTOR);
	// printf("rotation up: x: %f, y: %f, z: %f\n", rotation_up.x, rotation_up.y, rotation_up.z);

	t_vector	rotation;
	rotation = rt_add(rotation_right, rotation_up);

	// TODO: This may feel better when used in the rt_add() statement below.
	// t_vector	offet_rotation;
	// offet_rotation = rt_add(data->camera->normal, rotation);

	data->camera->normal = rt_normalized(rt_add(data->camera->normal, rotation));
	// printf("camera forward normal: x: %f, y: %f, z: %f\n", data->camera->normal.x, data->camera->normal.y, data->camera->normal.z);

	data->moved_cursor = true;
}

static void	rt_init_pixel_lookup_indices(t_data *data)
{
	uint32_t	index;

	index = 0;
	while (index < WINDOW_WIDTH * WINDOW_HEIGHT)
	{
		data->pixel_lookup_indices[index] = index;
		index++;
	}

	size_t	length;
	length = WINDOW_WIDTH * WINDOW_HEIGHT;

	while (length > 1)
	{
		index = rt_rand() % length;

		length--;

		uint32_t	temp;

		temp = data->pixel_lookup_indices[index];
		data->pixel_lookup_indices[index] = data->pixel_lookup_indices[length];
		data->pixel_lookup_indices[length] = temp;
	}
}

t_status	rt_init(int argc, char *argv[], t_data *data)
{
	ft_bzero(data, sizeof(*data));
	if (argc != 2)
		return (rt_print_error(ERROR_INVALID_ARGC));
	if (rt_parse_argv(argv, data) == ERROR)
		return (ERROR);
	rt_assign_capitalized_objects(data);
	if (rt_camera_is_invalid(data))
		return (rt_print_error(ERROR_INVALID_CAMERA_NORMAL));
	rt_debug_print_objects(data);
	data->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, false);
	if (data->mlx == NULL || !mlx_loop_hook(data->mlx, &rt_draw_loop, data))
		return (rt_print_error(ERROR_MLX));

	mlx_key_hook(data->mlx, &rt_key_hook, data);
	mlx_cursor_hook(data->mlx, &rt_cursor_hook, data);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
	// mlx_cursorfunc
	// mlx_win_cursor_t
	// mlx_get_mouse_pos
	// mlx_set_cursor
	// mlx_set_mouse_pos

	rt_update_canvas_info(data);
	data->draw_debug = DEBUG_DRAWING_ON_BY_DEFAULT;

	data->image = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (data->image == NULL)
		return (rt_print_error(ERROR_MLX));

	int	instance_index;
	instance_index = mlx_image_to_window(data->mlx, data->image, 0, 0);
	if (instance_index < 0)
		return (rt_print_error(ERROR_MLX));

	data->window_center_x = WINDOW_WIDTH / 2;
	data->window_center_y = WINDOW_HEIGHT / 2;

	rt_init_pixel_lookup_indices(data);

	return (OK);
}
