/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_plane_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 22:55:00 by alphbarr          #+#    #+#             */
/*   Updated: 2025/05/16 22:55:00 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	parse_plane_position(t_plane *plane, char *pos_str)
{
	char	**pos;

	pos = ft_split(pos_str, ',');
	if (!validate_coordinates(pos, "Invalid plane position", pos_str))
		return;
	plane->point.x = ft_atoif(pos[0]);
	plane->point.y = ft_atoif(pos[1]);
	plane->point.z = ft_atoif(pos[2]);
	free_split(pos);
}

void	parse_plane_normal(t_plane *plane, char *normal_str)
{
	char	**trid;

	trid = ft_split(normal_str, ',');
	if (!validate_coordinates(trid, "Invalid plane normal", normal_str))
		return;
	plane->normal.x = ft_atoif(trid[0]);
	plane->normal.y = ft_atoif(trid[1]);
	plane->normal.z = ft_atoif(trid[2]);
	free_split(trid);
}

int	parse_plane_color(t_plane *plane, char *color_str)
{
	char	**rgb;

	if (!color_str)
	{
		parse_error("Plane color missing", NULL);
		return (0);
	}
	rgb = ft_split(color_str, ',');
	if (!validate_color_values(rgb, "Invalid plane color", color_str))
		return (0);
	plane->color.r = ft_atoi(rgb[0]);
	plane->color.g = ft_atoi(rgb[1]);
	plane->color.b = ft_atoi(rgb[2]);
	if (!validate_color_component(plane->color.r, rgb[0],
			"Plane red value out of range"))
		return (0);
	if (!validate_color_component(plane->color.g, rgb[1],
			"Plane green value out of range"))
		return (0);
	if (!validate_color_component(plane->color.b, rgb[2],
			"Plane blue value out of range"))
		return (0);
	free_split(rgb);
	return (1);
}

t_plane	*set_plane_properties(void)
{
	t_plane	*plane;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		parse_error("Memory allocation failed for plane", NULL);
	init_plane(plane);
	return (plane);
}

