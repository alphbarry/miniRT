/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpha <alpha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:37:41 by alpha             #+#    #+#             */
/*   Updated: 2025/04/21 19:37:41 by alpha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

/*
** Calculate ambient light contribution
*/

t_vec3	ft_calculate_ambient(t_ambient ambient, t_vec3 obj_color)
{
	t_vec3	ambient_color;

	ambient_color = ft_vec3_mult(ambient.color, ambient.intensity);
	return (ft_vec3_color_mult(ambient_color, obj_color));
}

/*
** Check if a point is in shadow for a specific light
*/

int	ft_is_in_shadow(t_vec3 point, t_vec3 light_dir, double light_dist, 
		t_scene scene)
{
	t_ray	shadow_ray;
	t_hit	shadow_hit;
	int		i;

	shadow_ray.origin = ft_vec3_add(point, ft_vec3_mult(light_dir, EPSILON));
	shadow_ray.dir = light_dir;
	i = 0;
	while (i < scene.object_count)
	{
		if (scene.objects[i].type == SPHERE)
			shadow_hit = ft_intersect_sphere(shadow_ray, 
					scene.objects[i].u.sphere);
		else if (scene.objects[i].type == PLANE)
			shadow_hit = ft_intersect_plane(shadow_ray, 
					scene.objects[i].u.plane);
		if (shadow_hit.hit && shadow_hit.t < light_dist)
			return (1);
		i++;
	}
	return (0);
}

/*
** Calculate diffuse lighting from a point light
*/

t_vec3	ft_calculate_diffuse(t_hit hit, t_light light, t_scene scene)
{
	t_vec3	light_dir;
	double	light_dist;
	double	diffuse_factor;
	t_vec3	diffuse_color;

	light_dir = ft_vec3_sub(light.position, hit.point);
	light_dist = ft_vec3_length(light_dir);
	light_dir = ft_vec3_normalize(light_dir);
	if (ft_is_in_shadow(hit.point, light_dir, light_dist, scene))
		return (ft_vec3_create(0, 0, 0));
	diffuse_factor = fmax(0.0, ft_vec3_dot(hit.normal, light_dir));
	diffuse_color = ft_vec3_mult(light.color, light.intensity * diffuse_factor);
	return (ft_vec3_color_mult(diffuse_color, hit.color));
}

/*
** Calculate the combined light contribution from all sources
*/

t_vec3	ft_calculate_light(t_hit hit, t_scene scene)
{
	t_vec3	color;
	t_vec3	ambient_color;
	t_vec3	light_color;
	int		i;

	ambient_color = ft_calculate_ambient(scene.ambient, hit.color);
	color = ambient_color;
	i = 0;
	while (i < scene.light_count)
	{
		light_color = ft_calculate_diffuse(hit, scene.lights[i], scene);
		color = ft_vec3_add(color, light_color);
		i++;
	}
	color = ft_vec3_clamp(color, 0.0, 1.0);
	return (color);
}

/*
** Initialize ambient light with given parameters
*/

void	ft_init_ambient(t_ambient *ambient, double intensity, t_vec3 color)
{
	ambient->intensity = fmin(1.0, fmax(0.0, intensity));
	ambient->color = ft_vec3_clamp(color, 0.0, 1.0);
}

/*
** Initialize a point light with given parameters
*/

void	ft_init_light(t_light *light, t_vec3 position, double intensity, 
		t_vec3 color)
{
	light->position = position;
	light->intensity = fmin(1.0, fmax(0.0, intensity));
	light->color = ft_vec3_clamp(color, 0.0, 1.0);
}

