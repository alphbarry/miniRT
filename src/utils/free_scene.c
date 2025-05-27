/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:50:04 by alphbarr          #+#    #+#             */
/*   Updated: 2025/05/23 18:12:35 by cgomez-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_scene(t_scene *scene)
{
	free_spheres(scene->spheres);
	free_planes(scene->planes);
	free_cylinders(scene->cylinders);
	free_lights(scene->lights);
}
