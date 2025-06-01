/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_shadow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:42:52 by alphbarr          #+#    #+#             */
/*   Updated: 2025/06/01 02:04:32 by cgomez-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	check_sphere_shadows(t_scene *scene, t_vector point, t_vector light_dir,
		float light_distance)
{
	float	t;
	int		i;

	i = 0;
	while (i < scene->sphere_count)
	{
		if (intersect_sphere(point, light_dir, scene->spheres[i], &t))
		{
			if (t > 0.0f && t < light_distance)
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_plane_shadows(t_scene *scene, t_vector point, t_vector light_dir,
		float light_distance)
{
	float	t;
	int		i;

	i = 0;
	while (i < scene->plane_count)
	{
		if (intersect_plane(point, light_dir, scene->planes[i], &t))
		{
			if (t > 0.0f && t < light_distance)
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_cylinder_shadows(t_scene *scene, t_vector point, t_vector light_dir,
		float light_distance)
{
	float	t;
	int		i;
	t_pixel	ray;

	i = 0;
	while (i < scene->cylinder_count)
	{
		ray.origin = point;
		ray.direction = light_dir;
		ray.x = 0;
		ray.y = 0;
		if (check_cylinder_hits(scene->cylinders[i], ray, &t) && t > 0.0f
			&& t < light_distance)
			return (1);
		i++;
	}
	return (0);
}

int	is_in_shadow(t_scene *scene, t_vector point, t_vector light_pos)
{
	t_vector	light_dir;
	float		light_distance;

	light_dir = vector_sub(light_pos, point);
	light_distance = vector_length(light_dir);
	light_dir = vector_normalize(light_dir);
	point = vector_add(point, vector_scale(light_dir, SHADOW_BIAS));
	if (check_sphere_shadows(scene, point, light_dir, light_distance))
		return (1);
	if (check_plane_shadows(scene, point, light_dir, light_distance))
		return (1);
	if (check_cylinder_shadows(scene, point, light_dir, light_distance))
		return (1);
	return (0);
}
