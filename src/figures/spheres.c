#include "../../inc/minirt.h"

//formule for intersection of ray and sphere: [ t = \frac{-b \pm \sqrt{b^2 - 4ac}}{2a}
int	intersect_sphere(t_vector origin, t_vector direction, t_sphere sphere, float *t)
{
	t_vector	oc;// oc is the vector from the ray origin to the sphere center
	float		a;// a is the dot product of the direction vector with itself
	float		b;// b is the dot product of the oc vector with the direction vector
	float		c;// c is the dot product of the oc vector with itself minus the square of the sphere's radius
	float		discriminant;// discriminant is b^2 - 4ac

	oc = vector_sub(origin, sphere.center);
	a = vector_dot(direction, direction);
	b = 2.0f * vector_dot(oc, direction);
	c = vector_dot(oc, oc) - (sphere.radius * sphere.radius);
	discriminant = ((b * b) - (4 * a * c));
	if (discriminant < 0)
		return (0);
	*t = (-b - sqrtf(discriminant)) / (2.0f * a);// t = (-b ± sqrt(discriminant)) / 2a
	return (1);
}

void	draw_sphere(t_mlx *mlx, t_scene *scene, t_sphere sphere)
{
	int			x;
	int			y;
	float		t;
	t_vector	ray_direction;
	t_vector	origin;
	t_color		color;
	t_vector	hit_point;
	t_vector	normal;

	origin = scene->camera.position;
	y = 0;
	while (y < mlx->win_y)
	{
		x = 0;
		while (x < mlx->win_x)
		{
			ray_direction = get_ray_direction(&scene->camera, mlx, x, y);
			if (intersect_sphere(origin, ray_direction, sphere, &t))
			{
				hit_point = vector_add(origin, vector_scale(ray_direction, t));
				normal = vector_normalize(vector_sub(hit_point, sphere.center));
				color = compute_lighting(scene, hit_point, normal, sphere.color);
				set_pixel(mlx, color, x, y);
			}
			x++;
		}
		y++;
	}
}
