/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:06:17 by alphbarr          #+#    #+#             */
/*   Updated: 2025/05/07 20:37:24 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	draw_sphere(t_mlx *mlx, t_sphere *sphere)
{
	int x;
	int y;
	int dx;
	int dy;
	int radius_squared;

	// Cuadrado del radio para comparar sin necesidad de usar sqrt
	radius_squared = sphere->radius * sphere->radius;
	y = 0;
	while (y < mlx->win_y)
	{
		x = 0;
		while (x < mlx->win_x)
		{
			// Calcula la distancia al cuadrado entre el punto (x, y) y el centro de la esfera
			dx = x - sphere->center.x;
			dy = y - sphere->center.y;
			if ((dx * dx + dy * dy) <= radius_squared)
			{
				// Solo se dibuja el píxel si está dentro de la esfera
				put_pixel(mlx, x, y, color_to_int(sphere->color));
			}
			x++;
		}
		y++;
	}
}

void draw_plane(t_mlx *mlx, t_plane *plane)
{
    int x, y;
    float projected_x, projected_y, projected_z;
    float scale_factor;
    int dx, dy;

    // Definir los puntos del plano 3D en términos de su normal y el punto de origen.
    // En un caso simplificado, tomaremos un conjunto de puntos en el plano para proyectarlos.
    
    y = 0;
    while (y < mlx->win_y)
    {
        x = 0;
        while (x < mlx->win_x)
        {
            // Proyectamos las coordenadas del plano en 2D, basándonos en la perspectiva.
            projected_x = (x - mlx->win_x / 2) / 500.0;
            projected_y = (y - mlx->win_y / 2) / 500.0;
            projected_z = (plane->point.x * plane->tridimensional.x + plane->point.y * plane->tridimensional.y + plane->point.z * plane->tridimensional.z);
            // Ajustar la escala por la perspectiva.
            scale_factor = 1.0 / (1 + projected_z); // Más cerca, mayor escala.
            // Calcula la distancia al plano proyectado
            dx = x - plane->point.x;
            dy = y - plane->point.y;
            // Verifica si el punto está dentro de la proyección del plano
            if ((dx * dx + dy * dy) <= 10000) // Puedes ajustar este valor para el tamaño del plano proyectado
            {
                // Si el punto está dentro de los límites del plano proyectado, dibuja el píxel
                put_pixel(mlx, x, y, color_to_int(plane->color));
            }
            x++;
        }
        y++;
    }
}


void	draw_scene(t_mlx *mlx, t_scene *scene)
{
	int i;

	fill_background(mlx, scene);
	i = 0;
	while (i < scene->sphere_count)
	{
		draw_sphere(mlx, &scene->spheres[i]);
		i++;
	}
	while (i < scene->plane_count)
	{
		draw_plane(mlx, &scene->planes[i]);
		i++;
	}
}
