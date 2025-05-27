/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:50:04 by alphbarr          #+#    #+#             */
/*   Updated: 2025/05/23 18:21:36 by cgomez-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	free_spheres(t_sphere *spheres)
{
	t_sphere	*tmp;

	if(spheres)
	{
     while (spheres)
	{
		tmp = spheres->next;
		free(spheres);
		spheres = tmp;
	}
	}
	}

void	free_planes(t_plane *planes)
{
	t_plane	*tmp;

	if(planes)
	{
	while (planes)
	{
		tmp = planes->next;
		free(planes);
		planes = tmp;
	}

	}
}

void	free_cylinders(t_cylinder *cylinders)
{
	t_cylinder	*tmp;

	if(cylinders)
	{
	while (cylinders)
	{
		tmp = cylinders->next;
		free(cylinders);
		cylinders = tmp;
	}

	}
}

void	free_lights(t_light *lights)
{
	t_light	*tmp;

	if(lights)
	{
while (lights)
	{
		tmp = lights->next;
		free(lights);
		lights = tmp;
	}

	}
	}
