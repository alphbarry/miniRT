/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:05:57 by alphbarr          #+#    #+#             */
/*   Updated: 2025/05/14 17:09:13 by alpha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_color	compute_lighting(t_vector point, t_vector normal, t_light light, t_color object_color)
{
	t_vector	light_dir;
	float		diffuse;
	t_color		final;

	light_dir = vector_normalize(vector_sub(light.position, point));
	diffuse = vector_dot(normal, light_dir);
	if (diffuse < 0)
		diffuse = 0;
	diffuse *= light.intensity;

	final.r = object_color.r * diffuse * (light.color.r / 255.0);
	final.g = object_color.g * diffuse * (light.color.g / 255.0);
	final.b = object_color.b * diffuse * (light.color.b / 255.0);

	// Clampear
	final.r = fmin(final.r, 255);
	final.g = fmin(final.g, 255);
	final.b = fmin(final.b, 255);

	return (final);
}
