/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 22:55:00 by alphbarr          #+#    #+#             */
/*   Updated: 2025/05/23 19:08:36 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	get_cylinder(t_scene *scene, char *line)
{
	char	**split;

	split = ft_split(line, ' ');
	if (!validate_split(split, "Split failed", line))
		return;
	init_cylinder(&scene->cylinders[scene->cylinder_count]);
	if (split[1])
		parse_cylinder_position(scene->cylinders, split[1]);
	else
		parse_error("Cylinder position missing", line);
	
	if (split[2])
		parse_cylinder_orientation(scene->cylinders, split[2]);
	else
		parse_error("Cylinder orientation missing", line);
	
	if (!parse_cylinder_dimensions(scene->cylinders, split[3], split[4]))
		return;
	
	if (!parse_cylinder_color(scene->cylinders, split[5]))
		return;
	
	scene->cylinder_count++;
	free_split(split);
}
