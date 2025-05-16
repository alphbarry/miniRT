/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_light_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 22:33:00 by alphbarr          #+#    #+#             */
/*   Updated: 2025/05/16 22:33:00 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	parse_light_position(t_light *light, char *pos_str)
{
	char	**pos;

	pos = ft_split(pos_str, ',');
	if (!validate_coordinates(pos, "Invalid light position", pos_str))
		return ;
	light->position.x = ft_atoif(pos[0]);
	light->position.y = ft_atoif(pos[1]);
	light->position.z = ft_atoif(pos[2]);
	free_split(pos);
}

int	parse_light_intensity(t_light *light, char *intensity_str)
{
	if (!intensity_str)
	{
		parse_error("Light intensity missing", NULL);
		return (0);
	}
	light->intensity = ft_atoif(intensity_str);
	if (!validate_numeric_range(light->intensity, 0, 1, 
			"Light intensity out of range"))
		return (0);
	return (1);
}

int	parse_light_color(t_light *light, char *color_str)
{
	char	**rgb;

	if (!color_str)
	{
		parse_error("Light color missing", NULL);
		return (0);
	}
	rgb = ft_split(color_str, ',');
	if (!validate_color_values(rgb, "Invalid light color", color_str))
		return (0);
	light->color.r = ft_atoi(rgb[0]);
	light->color.g = ft_atoi(rgb[1]);
	light->color.b = ft_atoi(rgb[2]);
	if (!validate_color_component(light->color.r, rgb[0], 
			"Light red value out of range"))
		return (0);
	if (!validate_color_component(light->color.g, rgb[1], 
			"Light green value out of range"))
		return (0);
	if (!validate_color_component(light->color.b, rgb[2], 
			"Light blue value out of range"))
		return (0);
	free_split(rgb);
	return (1);
}

t_light	*set_light_properties(void)
{
	t_light	*light;

	light = malloc(sizeof(t_light));
	if (!light)
		parse_error("Memory allocation failed for light", NULL);
	init_light(light);
	return (light);
}

