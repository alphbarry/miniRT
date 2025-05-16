/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:05:57 by alphbarr          #+#    #+#             */
/*   Updated: 2025/05/16 23:26:52 by alpha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/* Check if a point is in shadow by casting a ray towards the light source */
int	is_in_shadow(t_scene *scene, t_vector point, t_vector light_pos)
{
	t_vector	light_dir;
	float		light_distance;
	float		t;
	int			i;

	// Calculate direction and distance to light
	light_dir = vector_sub(light_pos, point);
	light_distance = vector_length(light_dir);
	light_dir = vector_normalize(light_dir);
	// Add a small offset to the starting point to prevent self-shadowing
	point = vector_add(point, vector_scale(light_dir, SHADOW_BIAS));
	// Check if any sphere blocks the light
	i = 0;
	while (i < scene->sphere_count)
	{
		if (intersect_sphere(point, light_dir, scene->spheres[i], &t))
		{
			if (t > 0.0f && t < light_distance)
				return (1); // In shadow
		}
		i++;
	}
	// Check if any plane blocks the light
	i = 0;
	while (i < scene->plane_count)
	{
		if (intersect_plane(point, light_dir, scene->planes[i], &t))
		{
			if (t > 0.0f && t < light_distance)
				return (1); // In shadow
		}
		i++;
	}
	// Check if any cylinder blocks the light
	i = 0;
	while (i < scene->cylinder_count)
	{
		if (intersect_cylinder(point, light_dir, scene->cylinders[i], &t))
		{
			if (t > 0.0f && t < light_distance)
				return (1); // In shadow
		}
		i++;
	}
	return (0);
}

/* Calculate lighting at a point, considering ambient, diffuse, specular lights and shadows */
t_color	compute_lighting(t_scene *scene, t_vector point, t_vector normal, t_color object_color)
{
	t_color	final_color;
	int		i;
	float	diffuse;
	t_vector	light_dir;
	t_vector	view_dir;
	t_vector	reflect_dir;
	float		specular;
	float	ambient_factor;
	int	in_shadow;
	float	light_factor;

	// Apply ambient light - provides minimum illumination to all surfaces
	// Add AMBIENT_BOOST to ensure a minimum amount of light even in shadow
	ambient_factor = scene->ambient.ratio + AMBIENT_BOOST;
	final_color.r = object_color.r * ambient_factor * (scene->ambient.color.r / 255.0);
	final_color.g = object_color.g * ambient_factor * (scene->ambient.color.g / 255.0);
	final_color.b = object_color.b * ambient_factor * (scene->ambient.color.b / 255.0);
	// Calculate view direction for specular highlights (from point towards camera)
	view_dir = vector_normalize(vector_scale(point, -1.0f)); // Assuming camera at origin
	i = 0;
	while (i < scene->light_count)
	{
		light_dir = vector_normalize(vector_sub(scene->lights[i].position, point));
		diffuse = vector_dot(normal, light_dir);
		in_shadow = is_in_shadow(scene, point, scene->lights[i].position);
		
		// Check if the point is not in shadow, then calculate lighting contribution
		if (!in_shadow)
		{
			light_factor = scene->lights[i].intensity * LIGHT_INTENSITY_SCALE;
			
			if (diffuse < 0)
				diffuse = 0;  // Surface faces away from light
			
			diffuse *= light_factor;

			// Calculate specular reflection
			reflect_dir = vector_normalize(vector_sub(
				vector_scale(normal, 2.0f * vector_dot(light_dir, normal)),
				light_dir));
			specular = pow(fmax(vector_dot(reflect_dir, view_dir), 0.0f), SPECULAR_SHININESS) * SPECULAR_INTENSITY;
			// Add diffuse contribution
			final_color.r += object_color.r * diffuse * (scene->lights[i].color.r / 255.0);
			final_color.g += object_color.g * diffuse * (scene->lights[i].color.g / 255.0);
			final_color.b += object_color.b * diffuse * (scene->lights[i].color.b / 255.0);
			// Add specular contribution (white highlights)
			final_color.r += 255.0f * specular;
			final_color.g += 255.0f * specular;
			final_color.b += 255.0f * specular;
		}
		i++;
	}
	// Apply improved color handling with smoother falloff (gamma correction approximation)
	final_color.r = 255.0f * sqrt(final_color.r / 255.0f);
	final_color.g = 255.0f * sqrt(final_color.g / 255.0f);
	final_color.b = 255.0f * sqrt(final_color.b / 255.0f);
	// Clamp color values to valid range
	if (final_color.r > 255) final_color.r = 255;
	if (final_color.g > 255) final_color.g = 255;
	if (final_color.b > 255) final_color.b = 255;
	return (final_color);
}

