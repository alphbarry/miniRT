/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:32:50 by alphbarr          #+#    #+#             */
/*   Updated: 2025/05/28 14:30:30 by cgomez-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/* Calculate intersection of ray with plane */
int	intersect_plane(t_vector origin, t_vector direction, t_plane plane,
		float *t)
{
	float		min_dist;
	t_vector	normal;
	float		denominator;
	float		numerator;

	min_dist = 0.001f;
	normal = vector_normalize(plane.normal);
	denominator = vector_dot(normal, direction);
	if (fabs(denominator) < min_dist)
		return (0);
	numerator = vector_dot(vector_sub(plane.point, origin), normal);
	*t = numerator / denominator;
	if (*t < min_dist)
		return (0);
	return (1);
}

/* Get the normal vector for a plane */
static t_vector	get_plane_normal(t_plane plane)
{
	t_vector	normal;

	normal = vector_normalize(plane.normal);
	return (normal);
}

/* Process a single pixel for plane rendering */
static void	process_plane_pixel(t_mlx *mlx, t_scene *scene, t_plane plane,
		t_pixel px)
{
	float		t;
	t_vector	hit_point;
	t_vector	normal;
	t_color		color;

	if (intersect_plane(px.origin, px.direction, plane, &t))
	{
		hit_point = vector_add(px.origin, vector_scale(px.direction, t));
		normal = get_plane_normal(plane);
		color = compute_lighting(scene, hit_point, normal, plane.color);
		set_pixel(mlx, color, px.x, px.y);
	}
}

/* Main plane rendering function */
void	draw_plane(t_mlx *mlx, t_scene *scene, t_plane plane)
{
	int			x;
	int			y;
	t_vector	origin;
	t_pixel		px;

	origin = scene->camera.position;
	y = 0;
	while (y < mlx->win_y)
	{
		x = 0;
		while (x < mlx->win_x)
		{
			px.origin = origin;
			px.direction = get_ray_direction(&scene->camera, mlx, x, y);
			px.x = x;
			px.y = y;
			process_plane_pixel(mlx, scene, plane, px);
			x++;
		}
		y++;
	}
}
