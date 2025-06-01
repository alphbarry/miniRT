/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgomez-z <cgomez-z@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:40:01 by cgomez-z          #+#    #+#             */
/*   Updated: 2025/06/01 23:42:11 by cgomez-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_vector	get_ray_direction(t_camera *camera, t_mlx *mlx, float x, float y)
{
	t_vector	direction;
	t_vector	basis[3];
	float		factor[3];

	factor[0] = (float)mlx->win_x / (float)mlx->win_y;
	factor[1] = tanf(camera->fov * 0.5f * M_PI / 180.0f);
	basis[0] = vector_normalize(camera->tridimensional);
	basis[2] = (t_vector){0.0f, 1.0f, 0.0f};
	if (fabs(vector_dot(basis[0], basis[2])) > 0.999f)
		basis[2] = (t_vector){0.0f, 0.0f, 1.0f};
	basis[1] = vector_normalize(vector_cross(basis[2], basis[0]));
	basis[2] = vector_cross(basis[0], basis[1]);
	factor[2] = (2.0f * ((x + 0.5f) / mlx->win_x) - 1.0f) * factor[0]
		* factor[1];
	direction = vector_scale(basis[1], factor[2]);
	factor[2] = (1.0f - 2.0f * ((y + 0.5f) / mlx->win_y)) * factor[1];
	direction = vector_add(direction, vector_scale(basis[2], factor[2]));
	direction = vector_add(direction, basis[0]);
	return (vector_normalize(direction));
}

void	set_pixel(t_mlx *mlx, t_color color, int x, int y)
{
	int	i;

	i = ((y * mlx->size_line) + (x * mlx->bpp / 8));
	mlx->img_data[i] = color.b;
	mlx->img_data[i + 1] = color.g;
	mlx->img_data[i + 2] = color.r;
}
