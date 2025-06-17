/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgomez-z <cgomez-z@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 02:24:55 by cgomez-z          #+#    #+#             */
/*   Updated: 2025/06/02 22:35:45 by cgomez-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	get_light(t_scene *scene, char *line)
{
	char	**split;
	char	**fields;

	fields = ft_split_all_spaces(line);
	if (!validate_field_count(fields, 4, "Invalid light definition", line))
	{
		free_split(fields);
		return ;
	}
	free_split(fields);
	split = ft_split_all_spaces(line);
	if (!validate_split(split, "Split failed", line))
		return ;
	init_light(&scene->lights[scene->light_count]);
	if (split[1])
		parse_light_position(scene->lights, split[1]);
	else
		parse_error("Light position missing", line);
	if (!parse_light_intensity(scene->lights, split[2]))
		return ;
	if (!parse_light_color(scene->lights, split[3]))
		return ;
	scene->light_count++;
	free_split(split);
}
