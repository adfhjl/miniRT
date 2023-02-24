/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   blue_noise.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/16 18:21:11 by sbos          #+#    #+#                 */
/*   Updated: 2023/02/16 18:21:11 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

				if (x < 0 || x >= UNSCALED_WINDOW_WIDTH || y < 0 || y >= UNSCALED_WINDOW_HEIGHT)
				{
					dx++;
					continue;
				}

				// We can't just get neighbor cells from available[],
				// so we use a second array that has available's values as its keys
				uint32_t	i;

				i = data->available_inverse[x + y * UNSCALED_WINDOW_WIDTH];

				uint32_t other_index;
				uint32_t other_x;
				uint32_t other_y;

				other_index = data->available[i];
				other_x = other_index % UNSCALED_WINDOW_WIDTH;
				other_y = other_index / UNSCALED_WINDOW_WIDTH;

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
		available_x = available_index % UNSCALED_WINDOW_WIDTH;
		available_y = available_index / UNSCALED_WINDOW_WIDTH;

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

	emptiest_x = emptiest_available % UNSCALED_WINDOW_WIDTH;
	emptiest_y = emptiest_available / UNSCALED_WINDOW_WIDTH;

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

static uint32_t	rt_min(uint32_t a, uint32_t b)
{
	if (a < b)
		return (a);
	return (b);
}

static uint32_t	rt_max(uint32_t a, uint32_t b)
{
	if (a > b)
		return (a);
	return (b);
}

void	rt_generate_noise(t_data *data)
{
	size_t		noise_gen_index;
	float		unavailable;
	uint32_t	update_radius;

	noise_gen_index = 0;
	while (noise_gen_index < GENERATED_NOISE_PER_FRAME && data->available_count > 0)
	{
		if (noise_gen_index % NOISE_PER_UPDATE_RADIUS_RECALCULATION == 0)
		{
			unavailable = rt_max(data->pixel_count - data->available_count, 1);
			update_radius = (uint32_t)(
					(float)data->starting_update_radius / sqrtf(unavailable));
			update_radius = rt_max(update_radius, 1);
			update_radius = rt_min(update_radius, MAX_UPDATE_RADIUS);
		}
		rt_remove_available(data, update_radius);
		noise_gen_index++;
	}
}
