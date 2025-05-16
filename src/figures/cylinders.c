/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinders.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:07:28 by alphbarr          #+#    #+#             */
/*   Updated: 2025/05/16 18:36:39 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"
/*
int	intersect_cylinder(t_vector origin, t_vector direction, t_cylinder cyl,
		float *t)
{
	t_vector	co;
	t_vector	axis;
	t_vector	d_proj;
	t_vector	co_proj;
	float		a;
	float		b;
	float		c;
	float		discriminant;
	float		sqrt_disc;
	float		t0;
	float		t1;
	float		tmp;
	float		y0;
	float		y1;

	co = vector_sub(origin, cyl.center);
	axis = vector_normalize(cyl.normal);
	d_proj = vector_sub(direction, vector_scale(axis, vector_dot(direction,
					axis)));
	co_proj = vector_sub(co, vector_scale(axis, vector_dot(co, axis)));
	a = vector_dot(d_proj, d_proj);
	b = 2.0f * vector_dot(d_proj, co_proj);
	c = vector_dot(co_proj, co_proj) - (cyl.radius * cyl.radius);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (0);
	sqrt_disc = sqrtf(discriminant);
	t0 = (-b - sqrt_disc) / (2.0f * a);
	t1 = (-b + sqrt_disc) / (2.0f * a);
	if (t0 > t1)
	{
		tmp = t0;
		t0 = t1;
		t1 = tmp;
	}
	y0 = vector_dot(axis, vector_sub(vector_add(origin, vector_scale(direction,
						t0)), cyl.center));
	y1 = vector_dot(axis, vector_sub(vector_add(origin, vector_scale(direction,
						t1)), cyl.center));
	if (y0 < 0 || y0 > cyl.height)
	{
		if (y1 < 0 || y1 > cyl.height)
			return (0);
		*t = t1;
	}
	else
		*t = t0;
	return (1);
}*/

int intersect_cylinder_cap(t_vector origin, t_vector direction, t_disk cap, float *t)
{
	float denom = vector_dot(direction, cap.normal);
	if (fabs(denom) < 1e-6)
		return 0;

	float t_temp = vector_dot(vector_sub(cap.center, origin), cap.normal) / denom;
	if (t_temp < 0)
		return 0;

	t_vector p = vector_add(origin, vector_scale(direction, t_temp));
	if (vector_length(vector_sub(p, cap.center)) > cap.radius)
		return 0;

	*t = t_temp;
	return 1;
}

int intersect_cylinder(t_vector origin, t_vector direction, t_cylinder cyl, float *t)
{
	// Normalize the cylinder axis
	t_vector axis = vector_normalize(cyl.normal);

	// Compute variables for quadratic equation
	t_vector oc = vector_sub(origin, cyl.center);

	float a = vector_dot(direction, direction) - powf(vector_dot(direction, axis), 2);
	float b = 2 * (vector_dot(direction, oc) - vector_dot(direction, axis) * vector_dot(oc, axis));
	float c = vector_dot(oc, oc) - powf(vector_dot(oc, axis), 2) - cyl.radius * cyl.radius;

	float discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return 0;

	float sqrt_disc = sqrtf(discriminant);
	float t0 = (-b - sqrt_disc) / (2 * a);
	float t1 = (-b + sqrt_disc) / (2 * a);

	if (t1 < 0)
		return 0;

	float y0 = vector_dot(axis, vector_add(oc, vector_scale(direction, t0)));
	float y1 = vector_dot(axis, vector_add(oc, vector_scale(direction, t1)));

	// Check if intersections are within cylinder height bounds
	float half_height = cyl.height / 2.0f;
	int valid0 = (t0 > 0 && y0 > -half_height && y0 < half_height);
	int valid1 = (t1 > 0 && y1 > -half_height && y1 < half_height);

	/*float t_cyl = INFINITY;

	if (valid0)
		t_cyl = t0;
	else if (valid1)
		t_cyl = t1;*/

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

	float	t_top = INFINITY;
	float	t_bot = INFINITY;
	int hit_top = intersect_cylinder_cap(origin, direction, top_cap, &t_top);
	int hit_bot = intersect_cylinder_cap(origin, direction, bot_cap, &t_bot);

	// Find closest valid intersection among cylinder body and caps
	float closest_t = INFINITY;
	if (valid0 && t0 < closest_t)
		closest_t = t0;
	if (valid1 && t1 < closest_t)
		closest_t = t1;
	if (hit_top && t_top > 0 && t_top < closest_t)
		closest_t = t_top;
	if (hit_bot && t_bot > 0 && t_bot < closest_t)
		closest_t = t_bot;

	if (closest_t == INFINITY)
		return 0;

	*t = closest_t;
	return 1;
}
