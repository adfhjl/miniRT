/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   voronoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/20 10:56:25 by sbos          #+#    #+#                 */
/*   Updated: 2023/02/20 10:56:25 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#include "draw/rt_draw.h"

static uint32_t	rt_get_sq_dist(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
{
	int32_t	dx;
	int32_t	dy;

	dx = x1 - x2;
	dy = y1 - y2;
	return ((uint32_t)(dx * dx + dy * dy));
}

static bool	rt_is_closer(int32_t startX, int32_t startY, int32_t x,
				int32_t y, uint32_t index, uint32_t *distances)
{
	uint32_t	sq_dist;

	sq_dist = rt_get_sq_dist(startX, startY, x, y);
	if (sq_dist < distances[index])
	{
		distances[index] = sq_dist;
		return (true);
	}
	return (false);
}

static uint32_t	rt_get_index(int32_t x, int32_t y)
{
	return ((uint32_t)(x + y * UNSCALED_WINDOW_WIDTH));
}

static bool	rt_is_valid(int32_t x, int32_t y, int32_t startX, int32_t startY, t_data *data)
{
	uint32_t	index;

	index = rt_get_index(x, y);
	return (!data->voronoi.visited[index] && rt_is_closer(startX, startY, x, y, index, data->voronoi.distances));
}

void	rt_voronoi_floodfill(int32_t start_x, int32_t start_y, t_rgb rgb,
			t_data *data)
{
	t_voronoi_seed	seed;
	int32_t			x;
	int32_t			y;
	t_voronoi		*voronoi;

	voronoi = &data->voronoi;
	seed = (t_voronoi_seed){start_x, start_y};
	ft_vector_push(&voronoi->stack, &seed);

	size_t	i;
	i = 0;
	while (i < data->pixel_count)
	{
		voronoi->visited[i] = false;
		i++;
	}

	voronoi->visited[rt_get_index(start_x, start_y)] = true;

	voronoi->distances[rt_get_index(start_x, start_y)] = 0;

	// TODO: Optimization is to skip putting pixels when they're already of that color

	// TODO: Optimization is to prioritize colors that have neighbors of different colors

	while (ft_vector_get_size(voronoi->stack) > 0)
	{
		seed = voronoi->stack[ft_vector_get_size(voronoi->stack) - 1];
		ft_vector_pop_back(&voronoi->stack);

		x = seed.x;
		y = seed.y;

		rt_put_pixel(data->image, (uint32_t)x, (uint32_t)y, rgb);

		if (y - 1 >= 0 && rt_is_valid(x, y - 1, start_x, start_y, data))
		{
			seed = (t_voronoi_seed){x, y - 1};
			voronoi->visited[rt_get_index(seed.x, seed.y)] = true;
			ft_vector_push(&voronoi->stack, &seed);
		}
		if (y + 1 < UNSCALED_WINDOW_HEIGHT && rt_is_valid(x, y + 1, start_x, start_y, data))
		{
			seed = (t_voronoi_seed){x, y + 1};
			voronoi->visited[rt_get_index(seed.x, seed.y)] = true;
			ft_vector_push(&voronoi->stack, &seed);
		}
		if (x - 1 >= 0 && rt_is_valid(x - 1, y, start_x, start_y, data))
		{
			seed = (t_voronoi_seed){x - 1, y};
			voronoi->visited[rt_get_index(seed.x, seed.y)] = true;
			ft_vector_push(&voronoi->stack, &seed);
		}
		if (x + 1 < UNSCALED_WINDOW_WIDTH && rt_is_valid(x + 1, y, start_x, start_y, data))
		{
			seed = (t_voronoi_seed){x + 1, y};
			voronoi->visited[rt_get_index(seed.x, seed.y)] = true;
			ft_vector_push(&voronoi->stack, &seed);
		}
	}
}
