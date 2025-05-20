/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:05:57 by alphbarr          #+#    #+#             */
/*   Updated: 2025/05/20 17:53:49 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/* Initialize parameters for lighting calculations */
void	initialize_light_calc(t_scene *scene, t_light_calc *calc)
{
	float	ambient_factor;

	if (!calc)
		return ;
	
	// Set ambient light parameters
	ambient_factor = scene->ambient.ratio + AMBIENT_BOOST;
	calc->ambient_factor = ambient_factor;
	calc->ambient_r = scene->ambient.color.r / 255.0;
	calc->ambient_g = scene->ambient.color.g / 255.0;
	calc->ambient_b = scene->ambient.color.b / 255.0;
	
	// Set light intensity scale
	calc->intensity_scale = LIGHT_INTENSITY_SCALE;
	
	// Set specular parameters
	calc->specular_shininess = SPECULAR_SHININESS;
	calc->specular_intensity = SPECULAR_INTENSITY;
}

/* Calculate the normalized direction vector from a point to a light source */
t_vector	get_light_direction(t_vector point, t_vector light_pos)
{
	t_vector	light_dir;
	//float		distance;

	// Calculate direction vector from point to light source
	light_dir = vector_sub(light_pos, point);
	
	// Store distance before normalization (might be useful for attenuation)
	//distance = vector_length(light_dir);
	
	// Normalize to get unit direction vector
	light_dir = vector_normalize(light_dir);
	
	return (light_dir);
}
