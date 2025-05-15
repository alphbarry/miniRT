/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:05:57 by alphbarr          #+#    #+#             */
/*   Updated: 2025/05/15 19:42:20 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_color	compute_lighting(t_scene *scene, t_vector point, t_vector normal, t_color object_color)
{
	t_color	final_color;
	int		i;
	float	diffuse;
	t_vector	light_dir;

	// Aplica luz ambiental
	final_color.r = object_color.r * scene->ambient.ratio * (scene->ambient.color.r / 255.0);
	final_color.g = object_color.g * scene->ambient.ratio * (scene->ambient.color.g / 255.0);
	final_color.b = object_color.b * scene->ambient.ratio * (scene->ambient.color.b / 255.0);

	// Para cada luz puntual
	i = 0;
	while (i < scene->light_count)
	{
		light_dir = vector_normalize(vector_sub(scene->lights[i].position, point));
		diffuse = vector_dot(normal, light_dir);
		if (diffuse > 0)
		{
			diffuse *= scene->lights[i].intensity;
			final_color.r += object_color.r * diffuse * (scene->lights[i].color.r / 255.0);
			final_color.g += object_color.g * diffuse * (scene->lights[i].color.g / 255.0);
			final_color.b += object_color.b * diffuse * (scene->lights[i].color.b / 255.0);
		}
		i++;
	}

	// Clamp color
	if (final_color.r > 255) final_color.r = 255;
	if (final_color.g > 255) final_color.g = 255;
	if (final_color.b > 255) final_color.b = 255;

	return (final_color);
}

