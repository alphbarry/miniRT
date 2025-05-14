#include "../../inc/minirt.h"

int	intersect_plane(t_vector origin, t_vector direction, t_plane plane, float *t)
{
	float	denominator;// denominator is the dot product of the plane normal and the ray direction
	float	numerator;// numerator is the dot product of the plane normal and the vector from the ray origin to the plane point

	denominator = vector_dot(plane.normal, direction);// the formula for the denominator is N * D
	if (fabs(denominator) < 1e-6)
		return (0);// the ray is parallel to the plane
	numerator = vector_dot(vector_sub(plane.point, origin), plane.normal);//the formule for the numerator is (P - O) * N
	*t = numerator / denominator;//t = (P - O) * N / (N * D)
	if (*t < 0)
		return (0);// the intersection is behind the ray origin
	return (1);
}

void	draw_plane(t_mlx *mlx, t_plane plane, t_camera camera)
{
	int		x;
	int		y;
	float	t;
	t_vector	ray_direction;
	t_vector	origin;
	t_color	color;

	origin = camera.position;
	y = 0;
	while (y < mlx->win_y)
	{
		x = 0;
		while (x < mlx->win_x)
		{
			ray_direction = get_ray_direction(&camera, mlx, x, y);
			if (intersect_plane(origin, ray_direction, plane, &t))
			{
				color = plane.color;
				set_pixel(mlx, color, x, y);
			}
			x++;
		}
		y++;
	}
}
