#include "../../inc/minirt.h"

int	intersect_plane(t_vector origin, t_vector direction, t_plane plane, float *t)
{
	float	denominator;
	float	numerator;
	t_vector normalized_normal;
	t_vector intersection_point;
	t_vector to_point;
	const float MIN_DIST = 0.001f; // Increased for better numerical stability
	const float PLANE_SIZE = 5.0f; // Limit plane to ±5 units from center point

	normalized_normal = vector_normalize(plane.normal);
	
	// Ensure normal points toward the ray origin if needed
	if (vector_dot(vector_sub(origin, plane.point), normalized_normal) < 0)
		normalized_normal = vector_scale(normalized_normal, -1.0f);
		
	denominator = vector_dot(normalized_normal, direction);
	
	// Check if ray is parallel to plane or pointing away
	if (fabs(denominator) < MIN_DIST)
		return (0);
	
	numerator = vector_dot(vector_sub(plane.point, origin), normalized_normal);
	*t = numerator / denominator;
	
	// Make sure intersection is in front of the camera
	if (*t < MIN_DIST)
		return (0);
		
	// Calculate the intersection point
	intersection_point = vector_add(origin, vector_scale(direction, *t));
	
	// Limit the plane's size by checking distance from center point
	to_point = vector_sub(intersection_point, plane.point);
	// Project the vector onto the plane
	to_point = vector_sub(to_point, 
		vector_scale(normalized_normal, vector_dot(to_point, normalized_normal)));
	
	// If point is too far from center, reject the intersection
	if (vector_length(to_point) > PLANE_SIZE)
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
