/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figures_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgomez-z <cgomez-z@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:34:05 by cgomez-z          #+#    #+#             */
/*   Updated: 2025/05/30 19:11:45 by cgomez-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"
/*
void	calc_cylinder_quadratic(t_cylinder cyl, t_pixel px,
			t_cyl_hit *hit, t_vector axis)
{
	t_vector	oc;
	float		dot_dir_axis;

	oc = vector_sub(px.origin, cyl.center);
	dot_dir_axis = vector_dot(px.direction, axis);
	hit->a = vector_dot(px.direction, px.direction)
		- powf(dot_dir_axis, 2);
	hit->b = 2 * (vector_dot(px.direction, oc)
		- dot_dir_axis * vector_dot(oc, axis));
	hit->c = vector_dot(oc, oc)
		- powf(vector_dot(oc, axis), 2)
		- cyl.radius * cyl.radius;
	hit->disc = hit->b * hit->b - 4 * hit->a * hit->c;
	hit->oc = oc;
	hit->axis = axis;
}*/
