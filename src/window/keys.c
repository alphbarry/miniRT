/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 19:10:09 by alphbarr          #+#    #+#             */
/*   Updated: 2025/06/02 00:16:14 by cgomez-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	is_key(int key)
{
	return (key == KEY_PLUS || key == KEY_PLUST || key == KEY_MINUS
		|| key == KEY_MINUST || key == KEY_8 || key == KEY_8T || key == KEY_2
		|| key == KEY_2T || key == KEY_UP || key == KEY_DOWN || key == KEY_LEFT
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

int	key_hook(int keycode, t_scene *scene, t_mlx *mlx)
{
	float	speed;

	speed = 10.0f;
	if (keycode == KEY_ESC)
		exit(0);
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
