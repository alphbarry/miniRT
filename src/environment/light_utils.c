/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgomez-z <cgomez-z@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:40:47 by cgomez-z          #+#    #+#             */
/*   Updated: 2025/06/01 23:56:34 by cgomez-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_color	calculate_ambient_light(t_scene *scene, t_color object_color)
{
	t_color	ambient_color;
	float	ambient_factor;

	ambient_factor = scene->ambient.ratio + AMBIENT_BOOST;
	ambient_color.r = object_color.r * ambient_factor * (scene->ambient.color.r
			/ 255.0);
	ambient_color.g = object_color.g * ambient_factor * (scene->ambient.color.g
			/ 255.0);
	ambient_color.b = object_color.b * ambient_factor * (scene->ambient.color.b
			/ 255.0);
	return (ambient_color);
}

t_color	calculate_diffuse_light(t_light light, t_vector normal,
		t_vector light_dir, t_color object_color)
{
	t_color	diffuse_color;
	float	diffuse;
	float	light_factor;

	diffuse = vector_dot(normal, light_dir);
	if (diffuse < 0)
		diffuse = 0;
	light_factor = light.intensity * LIGHT_INTENSITY_SCALE;
	diffuse *= light_factor;
	diffuse_color.r = object_color.r * diffuse * (light.color.r / 255.0);
	diffuse_color.g = object_color.g * diffuse * (light.color.g / 255.0);
	diffuse_color.b = object_color.b * diffuse * (light.color.b / 255.0);
	return (diffuse_color);
}

t_color	calculate_specular_light(t_vector light_dir, t_vector normal,
		t_vector view_dir)
{
	t_color		spec_color;
	t_vector	reflect_dir;
	float		specular;

	reflect_dir = vector_normalize(vector_sub(
				vector_scale(normal, 2.0f * vector_dot(light_dir, normal)),
				light_dir));
	specular = pow(fmax(vector_dot(reflect_dir, view_dir), 0.0f),
			SPECULAR_SHININESS) * SPECULAR_INTENSITY;
	spec_color.r = 255.0f * specular;
	spec_color.g = 255.0f * specular;
	spec_color.b = 255.0f * specular;
	return (spec_color);
}

t_color	apply_color_corrections(t_color color)
{
	t_color	corrected;

	corrected.r = 255.0f * sqrt(color.r / 255.0f);
	corrected.g = 255.0f * sqrt(color.g / 255.0f);
	corrected.b = 255.0f * sqrt(color.b / 255.0f);
	if (corrected.r > 255)
		corrected.r = 255;
	if (corrected.g > 255)
		corrected.g = 255;
	if (corrected.b > 255)
		corrected.b = 255;
	return (corrected);
}
