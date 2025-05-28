/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spheres.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:32:57 by alphbarr          #+#    #+#             */
/*   Updated: 2025/05/28 14:31:48 by cgomez-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/* Ray-sphere intersection formula */
int	intersect_sphere(t_vector origin, t_vector direction, t_sphere sphere,
		float *t)
{
	t_vector	oc;
	float		a;
	float		b;
	float		discriminant;

	oc = vector_sub(origin, sphere.center);
	a = vector_dot(direction, direction);
	b = 2.0f * vector_dot(oc, direction);
	discriminant = b * b - 4 * a * (vector_dot(oc, oc) - (sphere.radius
				* sphere.radius));
	if (discriminant < 0)
		return (0);
	*t = (-b - sqrtf(discriminant)) / (2.0f * a);
	return (1);
}

/* Calculate intersection point of ray with sphere */
static t_vector	get_sphere_intersection(t_vector origin, t_vector direction,
		float t)
{
	t_vector	hit_point;

	hit_point = vector_add(origin, vector_scale(direction, t));
	return (hit_point);
}

/* Calculate normal vector at sphere intersection point */
static t_vector	get_sphere_normal(t_vector hit_point, t_sphere sphere)
{
	t_vector	normal;

	normal = vector_normalize(vector_sub(hit_point, sphere.center));
	return (normal);
}

/* Process a single pixel for sphere rendering */
static void	process_sphere_pixel(t_mlx *mlx, t_scene *scene, t_sphere sphere,
		t_pixel px)
{
	float		t;
	t_vector	hit_point;
	t_vector	normal;
	t_color		color;

	if (intersect_sphere(px.origin, px.direction, sphere, &t))
	{
		hit_point = get_sphere_intersection(px.origin, px.direction, t);
		normal = get_sphere_normal(hit_point, sphere);
		color = compute_lighting(scene, hit_point, normal, sphere.color);
		set_pixel(mlx, color, px.x, px.y);
	}
}

/* Main sphere rendering function */
void	draw_sphere(t_mlx *mlx, t_scene *scene, t_sphere sphere)
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
			process_sphere_pixel(mlx, scene, sphere, px);
			x++;
		}
		y++;
	}
}
