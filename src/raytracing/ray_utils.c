/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgomez-z <cgomez-z@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:31:33 by cgomez-z          #+#    #+#             */
/*   Updated: 2025/05/30 01:48:14 by cgomez-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	update_trace_cylinder(t_trace *tr, t_cylinder *cy, t_cyhit info)
{
	t_vector	hit;
	t_vector	normal;
	t_vector	axis;
	t_vector	diff;

	hit = vector_add(info.origin, vector_scale(info.direction, info.t));
	axis = vector_normalize(cy->normal);
	diff = vector_sub(hit, cy->center);
	normal = vector_normalize(vector_sub(diff, vector_scale(axis,
					vector_dot(diff, axis))));
	tr->closest_t = info.t;
	tr->hit = hit;
	tr->normal = normal;
	tr->color = compute_lighting(info.scene, hit, normal, cy->color);
}
