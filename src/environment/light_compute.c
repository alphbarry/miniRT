/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_compute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgomez-z <cgomez-z@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:40:47 by cgomez-z          #+#    #+#             */
/*   Updated: 2025/06/01 02:02:21 by cgomez-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	prepare_lighting_vectors(t_vector point, t_vector *view_dir)
{
	*view_dir = vector_normalize(vector_scale(point, -1.0f));
}

void	add_light_contribution(t_scene *scene, t_light light,
		t_lighting_data *data)
{
	t_vector	light_dir;
	t_color		contrib;

	light_dir = vector_normalize(vector_sub(light.position, data->point));
	if (!is_in_shadow(scene, data->point, light.position))
	{
		contrib = calculate_diffuse_light(light, data->normal, light_dir,
				data->object_color);
		data->final_color = vector_add_color(data->final_color, contrib);
		contrib = calculate_specular_light(light_dir, data->normal,
				data->view_dir);
		data->final_color = vector_add_color(data->final_color, contrib);
	}
}

t_color	compute_lighting(t_scene *scene, t_vector point, t_vector normal,
		t_color object_color)
{
	t_lighting_data	data;
	int				i;

	data.point = point;
	data.normal = normal;
	data.object_color = object_color;
	data.final_color = calculate_ambient_light(scene, object_color);
	prepare_lighting_vectors(point, &data.view_dir);
	i = 0;
	while (i < scene->light_count)
	{
		add_light_contribution(scene, scene->lights[i], &data);
		i++;
	}
	return (apply_color_corrections(data.final_color));
}
