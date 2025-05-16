/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:50:04 by alphbarr          #+#    #+#             */
/*   Updated: 2025/05/16 19:51:20 by alphbarr         ###   ########.fr       */
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
	t_sphere	*tmp_s;
	t_plane		*tmp_p;
	t_cylinder	*tmp_c;
	t_light		*tmp_l;

	while (scene->spheres)
	{
		tmp_s = scene->spheres->next;
		free(scene->spheres);
		scene->spheres = tmp_s;
	}
	while (scene->planes)
	{
		tmp_p = scene->planes->next;
		free(scene->planes);
		scene->planes = tmp_p;
	}
	while (scene->cylinders)
	{
		tmp_c = scene->cylinders->next;
		free(scene->cylinders);
		scene->cylinders = tmp_c;
	}
	while (scene->lights)
	{
		tmp_l = scene->lights->next;
		free(scene->lights);
		scene->lights = tmp_l;
	}
}
