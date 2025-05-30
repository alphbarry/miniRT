/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinders.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:07:28 by alphbarr          #+#    #+#             */
/*   Updated: 2025/05/30 19:13:26 by cgomez-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

//Calculate cylinder body intersection (≤25 líneas)
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
/*
void	ft_valid_if(int v, float ts, float *t)
{
	if (v && ts < *t)
		*t = ts;
}

int	ft_valid_if1(float d)
{
	if (d < 0)
		return (0);
	return (1);
}

static int	check_cylinder_body(t_cylinder cyl, t_pixel px,
			t_cyl_hit *hit, float *t)
{
	t_vector	oc;
	t_vector	axis;
	float		y;
	float		d_dot;

	axis = vector_normalize(cyl.normal);
	oc = vector_sub(px.origin, cyl.center);
	d_dot = vector_dot(px.direction, axis);
	hit->a = vector_dot(px.direction, px.direction) - powf(d_dot, 2);
	hit->b = 2 * (vector_dot(px.direction, oc) - d_dot * vector_dot(oc, axis));
	hit->c = vector_dot(oc, oc) - powf(vector_dot(oc, axis), 2)
		- cyl.radius * cyl.radius;
	hit->disc = hit->b * hit->b - 4 * hit->a * hit->c;
	return (ft_valid_if1(hit->disc));
	hit->t0 = (-hit->b - sqrtf(hit->disc)) / (2 * hit->a);
	hit->t1 = (-hit->b + sqrtf(hit->disc)) / (2 * hit->a);
	return (ft_valid_if1(hit->t1));
	y = vector_dot(axis, vector_add(oc, vector_scale(px.direction, hit->t0)));
	hit->valid0 = (hit->t0 > 0 && y > -cyl.height / 2 && y < cyl.height / 2);
	y = vector_dot(axis, vector_add(oc, vector_scale(px.direction, hit->t1)));
	hit->valid1 = (hit->t1 > 0 && y > -cyl.height / 2 && y < cyl.height / 2);
	ft_valid_if(hit->valid0, hit->t0, t);
	ft_valid_if(hit->valid0, hit->t0, t);
	return (hit->valid0 || hit->valid1);
}
*/

/* Check cylinder (body + caps) intersection (≤25 líneas) */
int	check_cylinder_hits(t_cylinder cyl, t_pixel px, float *t)
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
	if (fabs(cap.denom) <= 1e-6)
		return (0);
	cap.center = vector_add(cyl.center, vector_scale(cap.axis, cyl.height
				/ 2.0f));
	cap.t_temp = vector_dot(vector_sub(cap.center, px.origin), cap.axis)
		/ cap.denom;
	if (!(cap.t_temp > 0 && cap.t_temp < *t))
		return (0);
	p = vector_add(px.origin, vector_scale(px.direction, cap.t_temp));
	dist = vector_length(vector_sub(p, cap.center));
	if (dist > cyl.radius)
		return (0);
	*t = cap.t_temp;
	return (1);
}

/* Calculate cylinder normal vector at hit point */
t_vector	get_cylinder_normal(t_vector hit_point, t_cylinder cyl)
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
	normal = get_cylinder_normal(hit_point, cylinder);
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

/*
#include "../../inc/minirt.h"

int	intersect_cylinder_cap(t_vector origin, t_vector direction, t_disk cap,
		float *t)
{
	float		t_temp;
	float		denom;
	t_vector	p;

	denom = vector_dot(direction, cap.normal);
	if (fabs(denom) < 1e-6)
		return (0);
	t_temp = vector_dot(vector_sub(cap.center, origin), cap.normal) / denom;
	if (t_temp < 0)
		return (0);
	p = vector_add(origin, vector_scale(direction, t_temp));
	if (vector_length(vector_sub(p, cap.center)) > cap.radius)
		return (0);
	*t = t_temp;
	return (1);
}

int	intersect_cylinder(t_vector origin, t_vector direction, t_cylinder cyl,
		float *t)
{
	t_vector	axis;
	float		t_top;
	float		t_bot;
	float		t0;
	float		t1;
	float		y0;
	float		y1;
	float		half_height;
	int			valid0;
	int			valid1;
	int			hit_top;
	int			hit_bot;
	float		a;
	float		b;
	float		c;
	float		discriminant;
	float		sqrt_disc;
	float		closest_t;
	t_vector	oc;

	// Normalize the cylinder axis
	axis = vector_normalize(cyl.normal);
	// Compute variables for quadratic equation
	oc = vector_sub(origin, cyl.center);
	a = vector_dot(direction, direction) - powf(vector_dot(direction, axis), 2);
	b = 2 * (vector_dot(direction, oc) - vector_dot(direction, axis)
			* vector_dot(oc, axis));
	c = vector_dot(oc, oc) - powf(vector_dot(oc, axis), 2) - cyl.radius
		* cyl.radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (0);
	sqrt_disc = sqrtf(discriminant);
	t0 = (-b - sqrt_disc) / (2 * a);
	t1 = (-b + sqrt_disc) / (2 * a);
	if (t1 < 0)
		return (0);
	y0 = vector_dot(axis, vector_add(oc, vector_scale(direction, t0)));
	y1 = vector_dot(axis, vector_add(oc, vector_scale(direction, t1)));
	// Check if intersections are within cylinder height bounds
	half_height = cyl.height / 2.0f;
	valid0 = (t0 > 0 && y0 > -half_height && y0 < half_height);
	valid1 = (t1 > 0 && y1 > -half_height && y1 < half_height);
	// Check caps intersections
	t_disk top_cap = {
		vector_add(cyl.center, vector_scale(axis, half_height)),
		axis,
		cyl.radius
	};
	t_disk bot_cap = {
		vector_sub(cyl.center, vector_scale(axis, half_height)),
		vector_scale(axis, -1),
		cyl.radius
	};
	t_top = INFINITY;
	t_bot = INFINITY;
	hit_top = intersect_cylinder_cap(origin, direction, top_cap, &t_top);
	hit_bot = intersect_cylinder_cap(origin, direction, bot_cap, &t_bot);
	// Find closest valid intersection among cylinder body and caps
	closest_t = INFINITY;
	if (valid0 && t0 < closest_t)
		closest_t = t0;
	if (valid1 && t1 < closest_t)
		closest_t = t1;
	if (hit_top && t_top > 0 && t_top < closest_t)
		closest_t = t_top;
	if (hit_bot && t_bot > 0 && t_bot < closest_t)
		closest_t = t_bot;
	if (closest_t == INFINITY)
		return (0);
	*t = closest_t;
	return (1);
}
*/
