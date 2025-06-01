/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx_ray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgomez-z <cgomez-z@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 01:09:09 by cgomez-z          #+#    #+#             */
/*   Updated: 2025/06/02 01:09:46 by cgomez-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	init_ray(t_ray *r)
{
	init_vector(&r->origin);
	init_vector(&r->direction);
}

void	allocate_objects(t_scene *scene)
{
	scene->spheres = malloc(sizeof(t_sphere) * scene->sphere_count);
	scene->planes = malloc(sizeof(t_plane) * scene->plane_count);
	scene->cylinders = malloc(sizeof(t_cylinder) * scene->cylinder_count);
	scene->lights = malloc(sizeof(t_light) * scene->light_count);
	if (!scene->spheres || !scene->planes || !scene->cylinders
		|| !scene->lights)
		parse_error("Memory allocation failed for objects", NULL);
	scene->sphere_count = 0;
	scene->plane_count = 0;
	scene->cylinder_count = 0;
	scene->light_count = 0;
}

void	init_data(t_data *data)
{
	init_mlx(&data->mlx);
	init_scene(&data->scene);
}
