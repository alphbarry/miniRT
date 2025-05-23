/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cylinder_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 22:45:00 by alphbarr          #+#    #+#             */
/*   Updated: 2025/05/23 19:36:23 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	parse_cylinder_position(t_cylinder *cylinder, char *pos_str)
{
	char	**pos;

	pos = ft_split(pos_str, ',');
	if (!validate_coordinates(pos, "Invalid cylinder position", pos_str))
		return;
	cylinder->center.x = ft_atoif(pos[0]);
	cylinder->center.y = ft_atoif(pos[1]);
	cylinder->center.z = ft_atoif(pos[2]);
	free_split(pos);
}

void	parse_cylinder_orientation(t_cylinder *cylinder, char *orient_str)
{
	char	**trid;

	trid = ft_split(orient_str, ',');
	if (!validate_coordinates(trid, "Invalid cylinder orientation", orient_str))
		return;
	cylinder->normal.x = ft_atoif(trid[0]);
	cylinder->normal.y = ft_atoif(trid[1]);
	cylinder->normal.z = ft_atoif(trid[2]);
	free_split(trid);
}

int	parse_cylinder_dimensions(t_cylinder *cylinder, char *radius_str, 
		char *height_str)
{
	if (!radius_str)
	{
		parse_error("Cylinder radius missing", NULL);
		return (0);
	}
	cylinder->radius = ft_atoif(radius_str);
	if (cylinder->radius <= 0)
	{
		parse_error("Cylinder radius must be positive", radius_str);
		return (0);
	}
	if (!height_str)
	{
		parse_error("Cylinder height missing", NULL);
		return (0);
	}
	cylinder->height = ft_atoif(height_str);
	if (cylinder->height <= 0)
	{
		parse_error("Cylinder height must be positive", height_str);
		return (0);
	}
	return (1);
}

int	parse_cylinder_color(t_cylinder *cylinder, char *color_str)
{
	char	**rgb;

	if (!color_str)
	{
		parse_error("Cylinder color missing", NULL);
		return (0);
	}
	rgb = ft_split(color_str, ',');
	if (!validate_color_values(rgb, "Invalid cylinder color", color_str))
		return (0);
	cylinder->color.r = ft_atoi(rgb[0]);
	cylinder->color.g = ft_atoi(rgb[1]);
	cylinder->color.b = ft_atoi(rgb[2]);
	if (!validate_color_component(cylinder->color.r, rgb[0],
			"Cylinder red value out of range"))
		return (0);
	if (!validate_color_component(cylinder->color.g, rgb[1],
			"Cylinder green value out of range"))
		return (0);
	if (!validate_color_component(cylinder->color.b, rgb[2],
			"Cylinder blue value out of range"))
		return (0);
	free_split(rgb);
	return (1);
}
