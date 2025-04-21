/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpha <alpha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:37:41 by alpha             #+#    #+#             */
/*   Updated: 2025/04/21 19:37:41 by alpha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

/*
** Initialize a hit structure with default values
*/

t_hit	ft_init_hit(void)
{
	t_hit	hit;

	hit.t = MAX_DISTANCE;
	hit.point = ft_vec3_create(0, 0, 0);
	hit.normal = ft_vec3_create(0, 0, 0);
	hit.color = ft_vec3_create(0, 0, 0);
	hit.hit = 0;
	return (hit);
}

/*
** Calculate point on ray at distance t
*/

t_vec3	ft_ray_at(t_ray ray, double t)
{
	return (ft_vec3_add(ray.origin, ft_vec3_mult(ray.dir, t)));
}

/*
** Check if a ray intersects with a sphere
** Uses quadratic formula: t = (-b ± √(b² - 4ac)) / 2a
*/

t_hit	ft_intersect_sphere(t_ray ray, t_sphere sphere)
{
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	t;
	t_hit	hit;

	hit = ft_init_hit();
	oc = ft_vec3_sub(ray.origin, sphere.center);
	a = ft_vec3_dot(ray.dir, ray.dir);
	b = 2.0 * ft_vec3_dot(oc, ray.dir);
	c = ft_vec3_dot(oc, oc) - sphere.radius * sphere.radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (hit);
	t = (-b - sqrt(discriminant)) / (2.0 * a);
	if (t < EPSILON)
	{
		t = (-b + sqrt(discriminant)) / (2.0 * a);
		if (t < EPSILON)
			return (hit);
	}
	hit.hit = 1;
	hit.t = t;
	hit.point = ft_ray_at(ray, t);
	hit.normal = ft_vec3_normalize(ft_vec3_sub(hit.point, sphere.center));
	hit.color = sphere.color;
	return (hit);
}

/*
** Check if a ray intersects with a plane
** Plane equation: dot(p - p0, n) = 0
** Ray equation: p = o + t * d
** Solving for t: t = dot(p0 - o, n) / dot(d, n)
*/

t_hit	ft_intersect_plane(t_ray ray, t_plane plane)
{
	double	denom;
	double	t;
	t_hit	hit;

	hit = ft_init_hit();
	denom = ft_vec3_dot(plane.normal, ray.dir);
	if (fabs(denom) < EPSILON)
		return (hit);
	t = ft_vec3_dot(ft_vec3_sub(plane.point, ray.origin), plane.normal) / denom;
	if (t < EPSILON || t > MAX_DISTANCE)
		return (hit);
	hit.hit = 1;
	hit.t = t;
	hit.point = ft_ray_at(ray, t);
	hit.normal = plane.normal;
	if (denom > 0)
		hit.normal = ft_vec3_mult(hit.normal, -1);
	hit.color = plane.color;
	return (hit);
}

/*
** Find the closest object intersection in the scene
*/

t_hit	ft_intersect_scene(t_ray ray, t_scene scene)
{
	int		i;
	t_hit	closest_hit;
	t_hit	current_hit;

	closest_hit = ft_init_hit();
	i = 0;
	while (i < scene.object_count)
	{
		if (scene.objects[i].type == SPHERE)
			current_hit = ft_intersect_sphere(ray, scene.objects[i].u.sphere);
		else if (scene.objects[i].type == PLANE)
			current_hit = ft_intersect_plane(ray, scene.objects[i].u.plane);
		if (current_hit.hit && current_hit.t < closest_hit.t)
			closest_hit = current_hit;
		i++;
	}
	return (closest_hit);
}

/*
** Create a ray from the camera to a pixel on the screen
*/

t_ray	ft_ray_create(t_vec3 origin, t_vec3 direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.dir = ft_vec3_normalize(direction);
	return (ray);
}

/*
** Get color from ray intersection with scene
*/

t_vec3	ft_ray_color(t_ray ray, t_scene scene)
{
	t_hit	hit;
	t_vec3	color;

	hit = ft_intersect_scene(ray, scene);
	if (hit.hit)
		color = ft_calculate_light(hit, scene);
	else
		color = ft_vec3_create(0.0, 0.0, 0.0);
	return (color);
}

