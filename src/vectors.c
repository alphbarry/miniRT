#include "../inc/minirt.h"

t_vector	vector_add(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

t_vector	vector_sub(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}

t_vector	vector_scale(t_vector a, float scalar)
{
	t_vector	result;

	result.x = a.x * scalar;
	result.y = a.y * scalar;
	result.z = a.z * scalar;
	return (result);
}

float	vector_dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vector	vector_normalize(t_vector a)
{
	float	length;
	t_vector	result;

	length = sqrtf(vector_dot(a, a));
	if (length == 0)
		return (a);
	result.x = a.x / length;
	result.y = a.y / length;
	result.z = a.z / length;
	return (result);
}

t_vector	vector_cross(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

t_vector	get_ray_direction(t_camera *camera, t_mlx *mlx, float x, float y)
{
	t_vector	direction;
	t_vector	basis[3]; // 0 = forward, 1 = right, 2 = up
	float		factor[3]; // factor[0] = aspect, [1] = fov_scale, [2] = dummy px/py reuse

	factor[0] = (float)mlx->win_x / (float)mlx->win_y;
	factor[1] = tanf(camera->fov * 0.5f * M_PI / 180.0f);

	basis[0] = vector_normalize(camera->tridimensional);
	basis[2] = (t_vector){0.0f, 1.0f, 0.0f};
	if (fabs(vector_dot(basis[0], basis[2])) > 0.999f)
		basis[2] = (t_vector){0.0f, 0.0f, 1.0f};
	basis[1] = vector_normalize(vector_cross(basis[2], basis[0]));
	basis[2] = vector_cross(basis[0], basis[1]);

	// px
	factor[2] = (2.0f * ((x + 0.5f) / mlx->win_x) - 1.0f) * factor[0] * factor[1];
	direction = vector_scale(basis[1], factor[2]);
	// py
	factor[2] = (1.0f - 2.0f * ((y + 0.5f) / mlx->win_y)) * factor[1];
	direction = vector_add(direction, vector_scale(basis[2], factor[2]));
	direction = vector_add(direction, basis[0]);

	return (vector_normalize(direction));
}

void	set_pixel(t_mlx *mlx, t_color color, int x, int y)
{
	int	i;

	i = ((y * mlx->size_line) + (x * mlx->bpp / 8));
	mlx->img_data[i] = color.b;
	mlx->img_data[i + 1] = color.g;
	mlx->img_data[i + 2] = color.r;
}

int	intersect_sphere(t_vector origin, t_vector direction, t_sphere sphere, float *t)
{
	t_vector	oc;
	float		a;
	float		b;
	float		c;
	float		discriminant;

	oc = vector_sub(origin, sphere.center);
	a = vector_dot(direction, direction);
	b = 2.0f * vector_dot(oc, direction);
	c = vector_dot(oc, oc) - (sphere.radius * sphere.radius);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (0);
	*t = (-b - sqrtf(discriminant)) / (2.0f * a);
	return (0);
}
