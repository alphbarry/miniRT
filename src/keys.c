/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 19:10:09 by alphbarr          #+#    #+#             */
/*   Updated: 2025/05/02 19:48:48 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

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

int	deal_key(int key, t_mlx *mlx)
{
	if (is_key(key))
	{
		new_image(mlx);
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
		print_menu(mlx);
	}
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
