/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_shadow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:42:52 by alphbarr          #+#    #+#             */
/*   Updated: 2025/05/30 00:49:24 by cgomez-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/* Check if any sphere blocks the light */
int	check_sphere_shadows(t_scene *scene, t_vector point, 
		t_vector light_dir, float light_distance)
{
	float	t;
	int		i;

	i = 0;
	while (i < scene->sphere_count)
	{
		if (intersect_sphere(point, light_dir, scene->spheres[i], &t))
		{
			if (t > 0.0f && t < light_distance)
				return (1); // In shadow
		}
		i++;
	}
	return (0);
}

/* Check if any plane blocks the light */
int	check_plane_shadows(t_scene *scene, t_vector point, 
		t_vector light_dir, float light_distance)
{
	float	t;
	int		i;

	i = 0;
	while (i < scene->plane_count)
	{
		if (intersect_plane(point, light_dir, scene->planes[i], &t))
		{
			if (t > 0.0f && t < light_distance)
				return (1); // In shadow
		}
		i++;
	}
	return (0);
}

/* Check if any cylinder blocks the light
int	check_cylinder_shadows(t_scene *scene, t_vector point, 
		t_vector light_dir, float light_distance)
{
	float	t;
	int		i;

	i = 0;
	while (i < scene->cylinder_count)
	{
		if (check_cylinder_hits(cyl, (t_pixel){origin, dir, 0, 0}, &t)
    && t < light_dist)
		{
			if (t > 0.0f && t < light_distance)
				return (1); // In shadow
		}
		i++;
	}
	return (0);
}*/

int	check_cylinder_shadows(t_scene *scene, t_vector point, 
		t_vector light_dir, float light_distance)
{
	float		t;
	int			i;
	t_pixel		ray;

	i = 0;
	while (i < scene->cylinder_count)
	{
		ray.origin = point;          // El origen del rayo de sombra es el punto
		ray.direction = light_dir;   // Dirección hacia la luz
		ray.x = 0;                   // Puedes poner 0 si no usas estas coordenadas
		ray.y = 0;

		// Usar el cilindro i-ésimo del arreglo/lista de cilindros
		if (check_cylinder_hits(scene->cylinders[i], ray, &t) && t > 0.0f && t < light_distance)
			return (1); // En sombra, hay un cilindro bloqueando la luz

		i++;
	}
	return (0);
}


/* Check if a point is in shadow by casting a ray towards the light source */
int	is_in_shadow(t_scene *scene, t_vector point, t_vector light_pos)
{
	t_vector	light_dir;
	float		light_distance;

	// Calculate direction and distance to light
	light_dir = vector_sub(light_pos, point);
	light_distance = vector_length(light_dir);
	light_dir = vector_normalize(light_dir);
	
	// Add a small offset to the starting point to prevent self-shadowing
	point = vector_add(point, vector_scale(light_dir, SHADOW_BIAS));
	
	// Check if any object blocks the light
	if (check_sphere_shadows(scene, point, light_dir, light_distance))
		return (1);
	if (check_plane_shadows(scene, point, light_dir, light_distance))
		return (1);
	if (check_cylinder_shadows(scene, point, light_dir, light_distance))
		return (1);
	
	return (0);
}

