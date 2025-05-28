/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinders.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:07:28 by alphbarr          #+#    #+#             */
/*   Updated: 2025/05/28 14:19:27 by cgomez-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/* Calculate cylinder body intersection */
static int	check_cylinder_body(t_cylinder cyl, t_pixel px, t_cyl_hit *hit,
		float *t)
{
	t_vector	oc;
	t_vector	axis;
	float		y;
	float		dot_dir_axis;

	axis = vector_normalize(cyl.normal);
	oc = vector_sub(px.origin, cyl.center);
	dot_dir_axis = vector_dot(px.direction, axis);
	hit->a = vector_dot(px.direction, px.direction) - powf(dot_dir_axis, 2);
	hit->b = 2 * (vector_dot(px.direction, oc) - dot_dir_axis * vector_dot(oc,
				axis));
	hit->c = vector_dot(oc, oc) - powf(vector_dot(oc, axis), 2) - cyl.radius
		* cyl.radius;
	hit->disc = hit->b * hit->b - 4 * hit->a * hit->c;
	if (hit->disc < 0)
		return (0);
	hit->t0 = (-hit->b - sqrtf(hit->disc)) / (2 * hit->a);
	hit->t1 = (-hit->b + sqrtf(hit->disc)) / (2 * hit->a);
	if (hit->t1 < 0)
		return (0);
	y = vector_dot(axis, vector_add(oc, vector_scale(px.direction, hit->t0)));
	hit->valid0 = (hit->t0 > 0 && y > -cyl.height / 2 && y < cyl.height / 2);
	y = vector_dot(axis, vector_add(oc, vector_scale(px.direction, hit->t1)));
	hit->valid1 = (hit->t1 > 0 && y > -cyl.height / 2 && y < cyl.height / 2);
	if (hit->valid0 && hit->t0 < *t)
		*t = hit->t0;
	if (hit->valid1 && hit->t1 < *t)
		*t = hit->t1;
	return (hit->valid0 || hit->valid1);
}

/* Check cylinder intersection including caps */
static int	check_cylinder_hits(t_cylinder cyl, t_pixel px, float *t)
{
	t_cyl_hit	hit;
	t_cap_hit	cap;
	t_vector	p;
	float		dist;

	*t = INFINITY;
	if (check_cylinder_body(cyl, px, &hit, t))
		return (1);
	cap.axis = vector_normalize(cyl.normal);
	cap.denom = vector_dot(px.direction, cap.axis);
	if (fabs(cap.denom) > 1e-6)
	{
		cap.center = vector_add(cyl.center, vector_scale(cap.axis, cyl.height
					/ 2.0f));
		cap.t_temp = vector_dot(vector_sub(cap.center, px.origin), cap.axis)
			/ cap.denom;
		if (cap.t_temp > 0 && cap.t_temp < *t)
		{
			p = vector_add(px.origin, vector_scale(px.direction, cap.t_temp));
			dist = vector_length(vector_sub(p, cap.center));
			if (dist <= cyl.radius)
			{
				*t = cap.t_temp;
				return (1);
			}
		}
	}
	return (0);
}

/* Calculate cylinder normal vector at hit point */
static t_vector	get_cylinder_normal(t_vector hit_point, t_cylinder cyl, float t)
{
	t_vector	axis;
	t_vector	cp;
	t_vector	normal;
	float		half_height;

	axis = vector_normalize(cyl.normal);
	half_height = cyl.height / 2.0f;
	cp = vector_sub(hit_point, cyl.center);
	if (fabs(vector_dot(cp, axis) - half_height) < 1e-5)
		return (axis);
	if (fabs(vector_dot(cp, axis) + half_height) < 1e-5)
		return (vector_scale(axis, -1));
	normal = vector_sub(cp, vector_scale(axis, vector_dot(cp, axis)));
	return (vector_normalize(normal));
}

/* Render a single cylinder pixel */
static void	cylinder_render_pixel(t_mlx *mlx, t_scene *scene,
		t_cylinder cylinder, t_pixel px)
{
	float		t;
	t_vector	hit_point;
	t_vector	normal;
	t_color		color;

	t = INFINITY;
	if (!check_cylinder_hits(cylinder, px, &t))
		return ;
	hit_point = vector_add(px.origin, vector_scale(px.direction, t));
	normal = get_cylinder_normal(hit_point, cylinder, t);
	color = compute_lighting(scene, hit_point, normal, cylinder.color);
	set_pixel(mlx, color, px.x, px.y);
}

/* Main cylinder drawing function */
void	draw_cylinder(t_mlx *mlx, t_scene *scene, t_cylinder cylinder)
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
			cylinder_render_pixel(mlx, scene, cylinder, px);
			x++;
		}
		y++;
	}
}
