/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ambient.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:06:09 by alphbarr          #+#    #+#             */
/*   Updated: 2025/05/14 16:51:15 by alpha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	get_ambient(t_scene *scene, char *line)
{
	char	**split;
	char	**rgb;

	split = ft_split(line, ' ');
	if (!split)
		parse_error("Split failed", line);
	init_ambient(&scene->ambient);
	if (split[1])
	{
		scene->ambient.ratio = ft_atoif(split[1]);
		if (scene->ambient.ratio < 0 || scene->ambient.ratio > 1)
			parse_error("Ambient ratio out of range", split[1]);
	}
	else
		parse_error("Ambient ratio missing", line);
	if (split[2])
	{
		rgb = ft_split(split[2], ',');
		if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
			parse_error("One of rgb missing", split[2]);
		scene->ambient.color.r = ft_atoi(rgb[0]);
		scene->ambient.color.g = ft_atoi(rgb[1]);
		scene->ambient.color.b = ft_atoi(rgb[2]);
		if (scene->ambient.color.r < 0 || scene->ambient.color.r > 255)
			parse_error("Red value out of range", rgb[0]);
		if (scene->ambient.color.g < 0 || scene->ambient.color.g > 255)
			parse_error("Green value out of range", rgb[1]);
		if (scene->ambient.color.b < 0 || scene->ambient.color.b > 255)
			parse_error("Blue value out of range", rgb[2]);
		free_split(rgb);
	}
	else
		parse_error("Ambient color missing", line);
	free_split(split);
}
