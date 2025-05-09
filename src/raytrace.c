/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:06:17 by alphbarr          #+#    #+#             */
/*   Updated: 2025/05/09 21:31:27 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	draw_sphere(t_mlx *mlx, t_sphere sphere, t_camera camera)
{
	int		x;
	int		y;
	float	t;
	t_vector	ray_direction;
	t_vector	origin;
	t_color	color;

	origin = camera.position;
	y = 0;
	while (y < mlx->win_y)
	{
		x = 0;
		while (x < mlx->win_x)
		{
			ray_direction = get_ray_direction(&camera, mlx, x, y);
			if (intersect_sphere(origin, ray_direction, sphere, &t))
			{
				color = sphere.color;
				set_pixel(mlx, color, x, y);
			}
			x++;
		}
		y++;
	}
}

void	draw_scene(t_mlx *mlx, t_scene *scene)
{
	int	i;

	fill_background(mlx, scene);
	i = 0;
	while (i < scene->sphere_count)
	{
		draw_sphere(mlx, scene->spheres[i], scene->camera);
		i++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
}
