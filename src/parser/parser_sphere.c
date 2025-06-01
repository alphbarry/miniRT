/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:47:00 by alphbarr          #+#    #+#             */
/*   Updated: 2025/06/01 02:28:09 by cgomez-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	get_sphere(t_scene *scene, char *line)
{
	char		**split;
	t_sphere	*new_sphere;

	split = ft_split(line, ' ');
	if (!validate_split(split, "Split failed", line))
		return ;
	init_sphere(&scene->spheres[scene->sphere_count]);
	new_sphere = &scene->spheres[scene->sphere_count];
	if (split[1])
		parse_sphere_position(new_sphere, split[1]);
	else
		parse_error("Sphere position missing", line);
	if (!parse_sphere_radius(new_sphere, split[2]))
		return ;
	if (!parse_sphere_color(new_sphere, split[3]))
		return ;
	scene->sphere_count++;
	free_split(split);
}
