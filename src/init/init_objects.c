/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgomez-z <cgomez-z@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 01:06:40 by cgomez-z          #+#    #+#             */
/*   Updated: 2025/06/02 01:07:11 by cgomez-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	init_sphere(t_sphere *sp)
{
	init_vector(&sp->center);
	sp->radius = 0.0f;
	init_color(&sp->color);
}

void	init_plane(t_plane *pl)
{
	init_vector(&pl->point);
	init_vector(&pl->normal);
	init_color(&pl->color);
}

void	init_cylinder(t_cylinder *cy)
{
	init_vector(&cy->center);
	init_vector(&cy->normal);
	cy->radius = 0.0f;
	cy->height = 0.0f;
	init_color(&cy->color);
}
