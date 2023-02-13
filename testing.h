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

typedef struct s_sphere
{
	t_vector	origin;
	float		diameter;
	t_rgb		rgb;
}	t_sphere;

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
