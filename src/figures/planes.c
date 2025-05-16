#include "../../inc/minirt.h"

int	intersect_plane(t_vector origin, t_vector direction, t_plane plane, float *t)
{
	float MIN_DIST;
	t_vector 	normalized_normal;
	float 	denominator;
	t_vector 	point_to_origin;
	float 	numerator;

	MIN_DIST = 0.001f;
	normalized_normal = vector_normalize(plane.normal);
	denominator = vector_dot(normalized_normal, direction);
	if (fabs(denominator) < MIN_DIST)
		return (0);
	point_to_origin = vector_sub(plane.point, origin);
	numerator = vector_dot(point_to_origin, normalized_normal);
	*t = numerator / denominator;
	if (*t < MIN_DIST)
		return (0);
	return (1);
}

void	draw_plane(t_mlx *mlx, t_scene *scene, t_plane plane)
{
	int		x;
	int		y;
	float	t;
	t_vector	ray_direction;
	t_vector	origin;
	t_color	color;


	origin = scene->camera.position;
	y = 0;
	while (y < mlx->win_y)
	{
		x = 0;
		while (x < mlx->win_x)
		{
			ray_direction = get_ray_direction(&scene->camera, mlx, x, y);
			if (intersect_plane(origin, ray_direction, plane, &t))
			{
				t_vector intersection_point;
				t_vector normalized_normal;
				
				intersection_point = vector_add(origin, vector_scale(ray_direction, t));
				normalized_normal = vector_normalize(plane.normal);
				color = compute_lighting(scene, intersection_point, normalized_normal, plane.color);
				set_pixel(mlx, color, x, y);
			}
			x++;
		}
		y++;
	}
}
