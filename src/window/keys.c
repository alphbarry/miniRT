/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 19:10:09 by alphbarr          #+#    #+#             */
/*   Updated: 2025/05/16 19:12:05 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	is_key(int key)
{
	return (key == KEY_PLUS || key == KEY_PLUST || key == KEY_MINUS
		|| key == KEY_MINUST
		|| key == KEY_8 || key == KEY_8T || key == KEY_2 || key == KEY_2T
		|| key == KEY_UP || key == KEY_DOWN || key == KEY_LEFT
		|| key == KEY_RIGHT || key == KEY_5 || key == KEY_5T || key == KEY_4
		|| key == KEY_4T || key == KEY_SPACE || key == KEY_6 || key == KEY_6T);
}

void	new_image(t_mlx *mlx)
{
	int	i;

	i = 0;
	while (i < mlx->size_line * mlx->win_y)
	{
		mlx->img_data[i] = 0;
		i++;
	}
}

void	rotate_camera(t_camera *camera, float angle_deg, char axis)
{
	float	angle = angle_deg * M_PI / 180.0;
	t_vector dir = camera->tridimensional;
	t_vector new_dir;

	if (axis == 'y') // rotar en eje Y (horizontal)
	{
		new_dir.x = dir.x * cos(angle) + dir.z * sin(angle);
		new_dir.y = dir.y;
		new_dir.z = -dir.x * sin(angle) + dir.z * cos(angle);
	}
	else if (axis == 'x') // rotar en eje X (vertical)
	{
		new_dir.x = dir.x;
		new_dir.y = dir.y * cos(angle) - dir.z * sin(angle);
		new_dir.z = dir.y * sin(angle) + dir.z * cos(angle);
	}
	camera->tridimensional = vector_normalize(new_dir);
}


int	key_hook(int keycode, t_scene *scene, t_mlx *mlx)
{
	float speed = 10.0f;

	if (keycode == KEY_ESC)
		exit(0);

	// Movimiento
	if (keycode == KEY_UP)
		scene->camera.position.y += speed;
	else if (keycode == KEY_DOWN)
		scene->camera.position.y -= speed;
	else if (keycode == KEY_LEFT)
		scene->camera.position.x -= speed;
	else if (keycode == KEY_RIGHT)
		scene->camera.position.x += speed;
	else if (keycode == KEY_PLUS || keycode == KEY_PLUST)
		scene->camera.position.z += speed;
	else if (keycode == KEY_MINUS || keycode == KEY_MINUST)
		scene->camera.position.z -= speed;

	// Rotación básica en eje horizontal (Y)
	else if (keycode == KEY_4 || keycode == KEY_4T)
		rotate_camera(&scene->camera, -5, 'y');
	else if (keycode == KEY_6 || keycode == KEY_6T)
		rotate_camera(&scene->camera, 5, 'y');

	// Redibujar la escena
	draw_scene(mlx, scene);
	return (0);
}


int	deal_key(int key, t_mlx *mlx)
{
	if (key == KEY_ESC)
	{
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr);
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
		exit(0);
	}
	return (0);
}
