/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   testing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbenneko <vbenneko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/18 14:02:31 by vbenneko      #+#    #+#                 */
/*   Updated: 2023/01/19 18:58:20 by vbenneko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_rgb
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_rgb;

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}	t_vector;

typedef struct s_vector	t_point;

typedef struct s_ray
{
	t_point		pos;
	t_vector	dir;
}	t_ray;

typedef struct s_light
{
	t_point		pos;
	float		str;
}	t_light;

typedef struct s_plane
{
	t_vector	normal;
	t_point		origin;
	t_rgb		color;
}	t_plane;

float	min_float(float a, float b)
{
	if (a > b)
		return (b);
	return (a);
}

t_point	get_ray_point(t_ray ray, float t)
{
	return ((t_point){
		.x = ray.pos.x + (t * ray.dir.x),
		.y = ray.pos.y + (t * ray.dir. y),
		.z = ray.pos.z + (t * ray.dir. z)
		});
}

float	dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vector	cross(t_vector a, t_vector b)
{
	return ((t_vector){
		.x = a.y * b.z - a.z * b.y,
		.y = a.z * b.x - a.x * b.z,
		.z = a.x * b.y - a.y * b.x
	});
}

t_vector	add(t_vector a, t_vector b)
{
	return ((t_vector){
		.x = a.x + b.x,
		.y = a.y + b.y,
		.z = a.z + b.z
	});
}

t_vector	sub(t_vector a, t_vector b)
{
	return ((t_vector){
		.x = a.x - b.x,
		.y = a.y - b.y,
		.z = a.z - b.z
	});
}

t_vector	scale(t_vector v, float f)
{
	return ((t_vector){
		.x = v.x * f,
		.y = v.y * f,
		.z = v.z * f
	});
}

float	mag2(t_vector v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

float	mag(t_vector v)
{
	return (sqrtf(mag2(v)));
}

t_vector	normalized(t_vector v)
{
	return (scale(v, 1 / mag(v)));
}

float	get_plane_collision_distance(t_ray ray, t_plane plane)
{
	float	n;

	n = dot(ray.dir, plane.normal);
	if (n == 0)
		return (INFINITY);
	return ((1 / n) * (dot(plane.origin, plane.normal) - dot(ray.pos, plane.normal)));
}

t_point	get_intersect_plane(t_ray ray, t_plane plane)
{
	float	dist;

	dist = get_plane_collision_distance(ray, plane);
	// if (dist == INFINITY)
	// 	return ();
	return (add(ray.pos, scale(ray.dir, dist)));
}

typedef enum e_type
{
	light,
	plane
}	t_type;

typedef struct s_objects
{
	struct s_objects	*next;
	union {
		t_light	light;
		t_plane	plane;
	};
	t_type				type;
}	t_objects;

int *vec = ft_vector_new(sizeof(t_object))
int value = 42;
ft_vector_push(&vec, &value);
vec[0]

t_rgb	get_ray_color(t_ray ray, t_objects *objects)
{
	// (void)ray;
	// (void)objects;
	t_objects	*obj;
	float		dist;

	dist = INFINITY;
	while (objects != NULL)
	{
		if (objects->type == plane)
		{
			dist = min_float(dist, get_plane_collision_distance(ray, objects->plane));
		}
		objects = objects->next;
	}
	if (dist == INFINITY)
		return ((t_rgb){.r = 0, .g = 0, .b = 0});

}

int	main(int argc, char *argv[])
{
	// Testing some maths
	{
		t_point	point;
		t_ray	ray;

		t_vector	a;
		t_vector	b;
		t_vector	c;
		float		result;
		t_plane		plane;

		(void)argc;
		(void)argv;

		ray = (t_ray){
			.pos = {.x = 0, .y = 0, .z = 0},
			.dir = {.x = 4, .y = 3, .z = 0}
		};
		point = get_ray_point(ray, 1);
		printf("A ray with position <(%f, %f, %f)> and direction <(%f, %f, %f)> with length <%d> ends at <(%f, %f, %f)>\n", ray.pos.x, ray.pos.y, ray.pos.z, ray.dir.x, ray.dir.y, ray.dir.z, 5, point.x, point.y, point.z);

		a = (t_vector){.x = 5, .y = 0, .z = 0};
		b = (t_vector){.x = 0, .y = 5, .z = 0};
		c =	cross(a, b);
		result = dot(a, b);
		printf("The dot product of vector a <(%f, %f, %f)> and vector b <(%f, %f, %f)> is %f\n", a.x, a.y, a.z, b.x, b.y, b.z, result);
		printf("The cross product of vector a <(%f, %f, %f)> and vector b <(%f, %f, %f)> is <(%f, %f, %f)>\n", a.x, a.y, a.z, b.x, b.y, b.z, c.x, c.y, c.z);

		plane = (t_plane){.origin = {.x = 0, .y = 0, .z = 0}, .normal = {.x = 0, .y = 1, .z = 0}};
		ray = (t_ray){
			.pos = {.x = 0, .y = 5, .z = 0},
			.dir = {.x = 8, .y = -5, .z = 4}
		};
		point = get_intersect_plane(ray, plane);
		printf("A ray with position <(%f, %f, %f)> and direction <(%f, %f, %f)> and a plane with origin <(%f, %f, %f)> and normal <(%f, %f, %f)> intersect at position <(%f, %f, %f)>\n", ray.pos.x, ray.pos.y, ray.pos.z, ray.dir.x, ray.dir.y, ray.dir.z, plane.origin.x, plane.origin.y, plane.origin.z, plane.normal.x, plane.normal.y, plane.normal.z, point.x, point.y, point.z);
	}

	{
		t_objects	*objects;

		// Make a plane
		objects = malloc(sizeof(t_objects)); objects->next = NULL; objects->type = plane;
		objects->plane.normal = (t_vector){.x = 0, .y = 1, .z = 0};
		objects->plane.origin = (t_point){.x = 0, .y = 0, .z = 0};
		objects->plane.color = (t_rgb){.r = 255, .g = 0, .b = 255};

		// Make a light
		objects->next = malloc(sizeof(t_objects)); objects->next->next = NULL; objects->next->type = light;
		objects->next->light.pos = (t_point){.x = 2, .y = 2, .z = 0};
		objects->next->light.str = 0.6;

		// Make a ray
		t_ray	ray = {
			.pos = {.x = 0, .y = 2, .z = 0},
			.dir = {.x = 0, .y = -1, .z = 0}
		};

		t_rgb	ray_color;

		ray_color = get_ray_color(ray, objects);

		// Free memory allocated
		free(objects->next);
		free(objects);
	}
	return (0);
}
