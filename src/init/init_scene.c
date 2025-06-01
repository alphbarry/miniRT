/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgomez-z <cgomez-z@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 01:07:21 by cgomez-z          #+#    #+#             */
/*   Updated: 2025/06/02 01:08:52 by cgomez-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	init_camera(t_camera *cam)
{
	init_vector(&cam->position);
	init_vector(&cam->tridimensional);
	cam->fov = 0.0f;
}

void	init_light(t_light *light)
{
	init_vector(&light->position);
	light->intensity = 0.0f;
	init_color(&light->color);
}

void	init_ambient(t_ambient *ambient)
{
	ambient->ratio = 0.0f;
	init_color(&ambient->color);
}

void	init_scene(t_scene *scene)
{
	init_camera(&scene->camera);
	scene->spheres = NULL;
	scene->planes = NULL;
	scene->cylinders = NULL;
	scene->lights = NULL;
	init_ambient(&scene->ambient);
	scene->sphere_count = 0;
	scene->plane_count = 0;
	scene->cylinder_count = 0;
	scene->light_count = 0;
}
