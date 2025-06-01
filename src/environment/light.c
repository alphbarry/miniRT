/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:05:57 by alphbarr          #+#    #+#             */
/*   Updated: 2025/06/01 02:01:51 by cgomez-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	initialize_light_calc(t_scene *scene, t_light_calc *calc)
{
	float	ambient_factor;

	if (!calc)
		return ;
	ambient_factor = scene->ambient.ratio + AMBIENT_BOOST;
	calc->ambient_factor = ambient_factor;
	calc->ambient_r = scene->ambient.color.r / 255.0;
	calc->ambient_g = scene->ambient.color.g / 255.0;
	calc->ambient_b = scene->ambient.color.b / 255.0;
	calc->intensity_scale = LIGHT_INTENSITY_SCALE;
	calc->specular_shininess = SPECULAR_SHININESS;
	calc->specular_intensity = SPECULAR_INTENSITY;
}

t_vector	get_light_direction(t_vector point, t_vector light_pos)
{
	t_vector	light_dir;

	light_dir = vector_sub(light_pos, point);
	light_dir = vector_normalize(light_dir);
	return (light_dir);
}
