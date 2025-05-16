/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sphere_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 22:38:00 by alphbarr          #+#    #+#             */
/*   Updated: 2025/05/16 22:38:00 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	parse_sphere_position(t_sphere *sphere, char *pos_str)
{
	char	**pos;

	pos = ft_split(pos_str, ',');
	if (!validate_coordinates(pos, "Invalid sphere position", pos_str))
		return;
	sphere->center.x = ft_atoif(pos[0]);
	sphere->center.y = ft_atoif(pos[1]);
	sphere->center.z = ft_atoif(pos[2]);
	free_split(pos);
}

int	parse_sphere_radius(t_sphere *sphere, char *radius_str)
{
	if (!radius_str)
	{
		parse_error("Sphere radius missing", NULL);
		return (0);
	}
	sphere->radius = ft_atoif(radius_str);
	if (sphere->radius <= 0)
	{
		parse_error("Sphere radius must be positive", radius_str);
		return (0);
	}
	return (1);
}

int	parse_sphere_color(t_sphere *sphere, char *color_str)
{
	char	**rgb;

	if (!color_str)
	{
		parse_error("Sphere color missing", NULL);
		return (0);
	}
	rgb = ft_split(color_str, ',');
	if (!validate_color_values(rgb, "Invalid sphere color", color_str))
		return (0);
	sphere->color.r = ft_atoi(rgb[0]);
	sphere->color.g = ft_atoi(rgb[1]);
	sphere->color.b = ft_atoi(rgb[2]);
	if (!validate_color_component(sphere->color.r, rgb[0],
			"Sphere red value out of range"))
		return (0);
	if (!validate_color_component(sphere->color.g, rgb[1],
			"Sphere green value out of range"))
		return (0);
	if (!validate_color_component(sphere->color.b, rgb[2],
			"Sphere blue value out of range"))
		return (0);
	free_split(rgb);
	return (1);
}

void	set_sphere_properties(t_scene *scene, t_sphere new_sphere)
{
	scene->sphere_count++;
	scene->spheres = realloc(scene->spheres, 
			scene->sphere_count * sizeof(t_sphere));
	if (!scene->spheres)
		parse_error("Memory allocation failed for spheres", NULL);
	scene->spheres[scene->sphere_count - 1] = new_sphere;
}

