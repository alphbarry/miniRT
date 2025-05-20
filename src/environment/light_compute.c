/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_compute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:46:13 by alphbarr          #+#    #+#             */
/*   Updated: 2025/05/20 17:46:13 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/* Calculate ambient light contribution */
t_color	calculate_ambient_light(t_scene *scene, t_color object_color)
{
	t_color	ambient_color;
	float	ambient_factor;

	// Apply ambient light - provides minimum illumination to all surfaces
	// Add AMBIENT_BOOST to ensure a minimum amount of light even in shadow
	ambient_factor = scene->ambient.ratio + AMBIENT_BOOST;
	ambient_color.r = object_color.r * ambient_factor * (scene->ambient.color.r / 255.0);
	ambient_color.g = object_color.g * ambient_factor * (scene->ambient.color.g / 255.0);
	ambient_color.b = object_color.b * ambient_factor * (scene->ambient.color.b / 255.0);
	return (ambient_color);
}

/* Calculate diffuse light contribution */
t_color	calculate_diffuse_light(t_light light, t_vector normal, 
		t_vector light_dir, t_color object_color)
{
	t_color	diffuse_color;
	float	diffuse;
	float	light_factor;

	diffuse = vector_dot(normal, light_dir);
	if (diffuse < 0)
		diffuse = 0;  // Surface faces away from light
	
	light_factor = light.intensity * LIGHT_INTENSITY_SCALE;
	diffuse *= light_factor;
	
	// Calculate diffuse contribution
	diffuse_color.r = object_color.r * diffuse * (light.color.r / 255.0);
	diffuse_color.g = object_color.g * diffuse * (light.color.g / 255.0);
	diffuse_color.b = object_color.b * diffuse * (light.color.b / 255.0);
	return (diffuse_color);
}

/* Calculate specular highlights */
t_color	calculate_specular_light(t_vector light_dir, t_vector normal, 
		t_vector view_dir)
{
	t_color		spec_color;
	t_vector	reflect_dir;
	float		specular;

	// Calculate specular reflection
	reflect_dir = vector_normalize(vector_sub(
		vector_scale(normal, 2.0f * vector_dot(light_dir, normal)),
		light_dir));
	specular = pow(fmax(vector_dot(reflect_dir, view_dir), 0.0f), 
		SPECULAR_SHININESS) * SPECULAR_INTENSITY;

	// Set specular contribution (white highlights)
	spec_color.r = 255.0f * specular;
	spec_color.g = 255.0f * specular;
	spec_color.b = 255.0f * specular;
	return (spec_color);
}

/* Apply gamma correction and color clamping */
t_color	apply_color_corrections(t_color color)
{
	t_color	corrected;

	// Apply improved color handling with gamma correction approximation
	corrected.r = 255.0f * sqrt(color.r / 255.0f);
	corrected.g = 255.0f * sqrt(color.g / 255.0f);
	corrected.b = 255.0f * sqrt(color.b / 255.0f);
	
	// Clamp color values to valid range
	if (corrected.r > 255)
		corrected.r = 255;
	if (corrected.g > 255)
		corrected.g = 255;
	if (corrected.b > 255)
		corrected.b = 255;
	return (corrected);
}

/* Main lighting function that coordinates all lighting calculations */
t_color	compute_lighting(t_scene *scene, t_vector point, 
		t_vector normal, t_color object_color)
{
	t_color		final_color;
	t_vector	light_dir;
	t_vector	view_dir;
	t_color		light_contribution;
	int			i;

	// Start with ambient light
	final_color = calculate_ambient_light(scene, object_color);
	
	// Calculate view direction for specular highlights
	view_dir = vector_normalize(vector_scale(point, -1.0f));
	
	// Process each light source
	i = 0;
	while (i < scene->light_count)
	{
		light_dir = vector_normalize(vector_sub(scene->lights[i].position, point));
		
		// Only calculate lighting if the point is not in shadow
		if (!is_in_shadow(scene, point, scene->lights[i].position))
		{
			// Add diffuse contribution
			light_contribution = calculate_diffuse_light(
				scene->lights[i], normal, light_dir, object_color);
			final_color.r += light_contribution.r;
			final_color.g += light_contribution.g;
			final_color.b += light_contribution.b;
			
			// Add specular contribution
			light_contribution = calculate_specular_light(
				light_dir, normal, view_dir);
			final_color.r += light_contribution.r;
			final_color.g += light_contribution.g;
			final_color.b += light_contribution.b;
		}
		i++;
	}
	
	// Apply gamma correction and clamping
	return (apply_color_corrections(final_color));
}

