/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 23:00:00 by alphbarr          #+#    #+#             */
/*   Updated: 2025/06/01 02:30:49 by cgomez-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	get_plane(t_scene *scene, char *line)
{
	char	**split;

	split = ft_split(line, ' ');
	if (!validate_split(split, "Split failed", line))
		return ;
	init_plane(&scene->planes[scene->plane_count]);
	if (split[1])
		parse_plane_position(scene->planes, split[1]);
	else
		parse_error("Plane position missing", line);
	if (split[2])
		parse_plane_normal(scene->planes, split[2]);
	else
		parse_error("Plane normal missing", line);
	if (!parse_plane_color(scene->planes, split[3]))
		return ;
	scene->plane_count++;
	free_split(split);
}
