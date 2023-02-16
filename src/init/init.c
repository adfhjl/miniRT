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
			mlx_put_pixel(image, x, y, (
					(uint32_t)UNRENDERED_R << 24)
				| ((uint32_t)UNRENDERED_G << 16)
				| ((uint32_t)UNRENDERED_B << 8)
				| 0xFF);
			x++;
		}
		y++;
	}
}

// Source: https://stackoverflow.com/a/11946674/13279557
static unsigned int	rt_rand(void)
{
	static unsigned int	seed = 1;

	seed = (seed * 1103515245U + 12345U) & 0x7fffffffU;
	return (seed);
}

static void	rt_reset_canvas_info(t_data *data)
{
	rt_update_canvas_info(data);
	rt_clear_image(data->image);
	data->pixel_index = data->pixel_count;
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

static void	rt_update_densities(t_data *data, uint32_t update_radius, uint32_t emptiest_x, uint32_t emptiest_y)
{
	int32_t	dx;
	int32_t	dy;

	// dy = (int32_t)fmaxf((float)-update_radius, (float)-emptiest_y);
	dy = (int32_t)-update_radius;
	while (dy <= (int32_t)update_radius)
	{
		// dx = (int32_t)fmaxf((float)-update_radius, (float)-emptiest_x);
		dx = (int32_t)-update_radius;
		while (dx <= (int32_t)update_radius)
		{
			// Only updates the density of cells that fall within the radius
			if ((uint32_t)(dx * dx + dy * dy) <= update_radius * update_radius)
			{
				int32_t	x;
				int32_t	y;

				x = (int32_t)emptiest_x + dx;
				y = (int32_t)emptiest_y + dy;

				if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
				{
					dx++;
					continue;
				}

				// We can't just get neighbor cells from available[],
				// so we use a second array that has available's values as its keys
				uint32_t	i;

				i = data->available_inverse[x + y * WINDOW_WIDTH];

				uint32_t other_index;
				uint32_t other_x;
				uint32_t other_y;

				other_index = data->available[i];
				other_x = other_index % WINDOW_WIDTH;
				other_y = other_index / WINDOW_WIDTH;

				int32_t	x_dist;
				int32_t	y_dist;
				float 	distance_squared;

				x_dist = (int32_t)emptiest_x - (int32_t)other_x;
				y_dist = (int32_t)emptiest_y - (int32_t)other_y;
				distance_squared = x_dist * x_dist + y_dist * y_dist;

				// Don't want to add density to filled cells
				if (i < data->available_count && distance_squared > 0)
				{
					data->densities[other_index] += 1 / distance_squared;
				}
			}
			dx++;
		}
		dy++;
	}
}

static void	rt_remove_available(t_data *data, uint32_t update_radius)
{
	float		emptiest;
	uint32_t	emptiest_available_index;

	emptiest = INFINITY;

	// TODO: I suspect a lot of time is spent in here, but I'm not sure without profiling.
	// If this is slow, look at v3 linked at the top for a priority queue example to try for a new v5.
	// Maybe sort on every insertion for fast lookup?
	uint32_t	i;

	i = 0;
	while (i < data->available_count)
	{
		uint32_t	available_index;
		uint32_t	available_x;
		uint32_t	available_y;

		available_index = data->available[i];
		available_x = available_index % WINDOW_WIDTH;
		available_y = available_index / WINDOW_WIDTH;

		float density = data->densities[available_index];

		if (density < emptiest)
		{
			emptiest = density;
			emptiest_available_index = i;
		}

		i++;
	}

	uint32_t	emptiest_available;

	emptiest_available = data->available[emptiest_available_index];

	uint32_t	emptiest_x;
	uint32_t	emptiest_y;

	emptiest_x = emptiest_available % WINDOW_WIDTH;
	emptiest_y = emptiest_available / WINDOW_WIDTH;

	rt_update_densities(data, update_radius, emptiest_x, emptiest_y);

	data->available_count--;

	uint32_t	a;
	uint32_t	b;

	a = data->available[emptiest_available_index];
	b = data->available[data->available_count];

	data->available[emptiest_available_index] = b;
	data->available[data->available_count] = a;

	data->available_inverse[b] = emptiest_available_index;
	data->available_inverse[a] = data->available_count;
}

static void	rt_generate_noise(t_data *data)
{
	size_t		noise_gen_index;
	uint32_t	update_radius;

	noise_gen_index = 0;
	while (noise_gen_index < GENERATED_NOISE_PER_FRAME && data->available_count > 0)
	{
		if (noise_gen_index % NOISE_PER_UPDATE_RADIUS_RECALCULATION == 0)
		{
			const float	unavailable = fmaxf(data->pixel_count - data->available_count, 1);
			update_radius = (uint32_t)fmaxf(data->starting_update_radius / sqrtf(unavailable), 1);
		}
		rt_remove_available(data, update_radius);
		noise_gen_index++;
	}
}

static void	rt_shoot_rays(t_data *data)
{
	t_ray		ray;
	t_rgb		rgb;
	size_t	ray_index;

	ray_index = 0;
	while (ray_index < RAYS_PER_FRAME && data->pixel_index > data->available_count)
	{
		data->pixel_index--;
		uint32_t location = data->available[data->pixel_index];
		uint32_t x = location % WINDOW_WIDTH;
		uint32_t y = location / WINDOW_WIDTH;
		ray = rt_create_ray(x, y, data); // TODO: Revamp this function to not recalculate stuff unnecesarally
		rgb = rt_get_ray_rgb(ray, data);
		mlx_put_pixel(data->image, x, y, rt_convert_color(rgb));
		ray_index++;
	}
}

static void	rt_update_camera_origin(t_data *data)
{
	float delta_move = MOVEMENT_STEP_SIZE * (float)data->mlx->delta_time;

	if (data->w_held)
		data->camera->origin = rt_get_ray_point(rt_get_ray(data->camera->origin, data->camera->normal), delta_move);
	if (data->a_held)
		data->camera->origin = rt_get_ray_point(rt_get_ray(data->camera->origin, data->camera_right), -delta_move);
	if (data->s_held)
		data->camera->origin = rt_get_ray_point(rt_get_ray(data->camera->origin, data->camera->normal), -delta_move);
	if (data->d_held)
		data->camera->origin = rt_get_ray_point(rt_get_ray(data->camera->origin, data->camera_right), delta_move);
	if (data->space_held)
		data->camera->origin = rt_get_ray_point(rt_get_ray(data->camera->origin, data->camera_up), delta_move);
	if (data->shift_held)
		data->camera->origin = rt_get_ray_point(rt_get_ray(data->camera->origin, data->camera_up), -delta_move);
}

static void	rt_draw_loop(void *param)
{
	t_data *const	data = param;

	if (rt_any_movement_key_pressed(data) || data->moved_cursor)
		rt_reset_canvas_info(data);
	data->moved_cursor = false;

	mlx_set_mouse_pos(data->mlx, data->window_center_x, data->window_center_y);

	rt_update_camera_origin(data);

	rt_generate_noise(data);
	rt_shoot_rays(data);

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
	float	dx;
	float	dy;

	data = param;
	// printf("xpos: %f, ypos: %f\n", xpos, ypos);
	dx = (float)xpos - data->window_center_x;
	dy = -((float)ypos - data->window_center_y);
	// printf("dx: %f, dy: %f\n", dx, dy);

	const float	delta_cursor_move = ROTATION_FACTOR * (float)data->mlx->delta_time;

	t_vector	rotation_right;
	rotation_right = rt_scale(data->camera_right, (float)dx * delta_cursor_move);
	// printf("rotation right: x: %f, y: %f, z: %f\n", rotation_right.x, rotation_right.y, rotation_right.z);
	t_vector	rotation_up;
	rotation_up = rt_scale(data->camera_up, (float)dy * delta_cursor_move);
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

static void	rt_shuffle(uint32_t *arr, size_t length)
{
	uint32_t	index;
	uint32_t	temp;

	while (length > 1)
	{
		index = rt_rand() % length;
		length--;
		temp = arr[index];
		arr[index] = arr[length];
		arr[length] = temp;
	}
}

static void	rt_init_available(t_data *data)
{
	uint32_t	index;

	index = 0;
	while (index < data->pixel_count)
	{
		data->available[index] = index;
		data->densities[index] = 0;
		index++;
	}

	rt_shuffle(data->available, data->pixel_count);

	uint32_t	value;
	index = 0;
	while (index < data->pixel_count)
	{
		value = data->available[index];
		data->available_inverse[value] = index;
		index++;
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
	// TODO: Experiment with changing the cursor icon to a hand
	// when the user rotates an object, or even the camera?
	// mlx_set_cursor
	// mlx_set_mouse_pos

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

	data->pixel_count = WINDOW_WIDTH * WINDOW_HEIGHT;
	data->available_count = data->pixel_count;

	rt_init_available(data);

	rt_reset_canvas_info(data);

	// SQRT2, because radius is circular.
	// It is the width/height multiplier necessary to reach the bottom-right
	// of the canvas starting from the top-left of the canvas.
	data->starting_update_radius = fmaxf(WINDOW_WIDTH * (float)M_SQRT2, WINDOW_HEIGHT * (float)M_SQRT2);
	// printf("starting_update_radius: %f\n", data->starting_update_radius);

	return (OK);
}
