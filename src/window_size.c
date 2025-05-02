/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 19:34:22 by alphbarr          #+#    #+#             */
/*   Updated: 2025/05/02 19:45:55 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

static int	check_window_size(int key, t_mlx *mlx)
{
	if ((key == 0 && mlx->win_y <= 500) || (key == 6 && mlx->win_x <= 500))
		return (1);
	if ((key == 1 && mlx->win_y > 1000) || (key == 7 && mlx->win_x > 2000))
		return (1);
	return (0);
}

void	full_screen(t_mlx *mlx)
{
	static int	old_x;
	static int	old_y;

	if (mlx->win_x != 2560)
	{
		old_x = mlx->win_x;
		old_y = mlx->win_y;
	}
	if (mlx->win_x == 2560)
	{
		mlx->win_x = old_x;
		mlx->win_y = old_y;
	}
	else
	{
		mlx->win_x = 2560;
		mlx->win_y = 1440;
	}
}

void	change_window_size(int key, t_mlx *mlx)
{
	if (check_window_size(key, mlx))
		return ;
	if (key == 6)
		mlx->win_y -= 100;
	if (key == 7)
		mlx->win_y += 100;
	if (key == 0)
		mlx->win_x -= 100;
	if (key == 1)
		mlx->win_x += 100;
	if (key == 3)
		full_screen(mlx);
}

void	update_window(int key, t_mlx *mlx)
{
	change_window_size(key, mlx);
	mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr);
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, mlx->win_x, mlx->win_y,
			"miniRT");
	mlx->shift_x = mlx->win_x / 3;
	mlx->shift_y = mlx->win_y / 3;
	mlx_key_hook(mlx->win_ptr, deal_key, mlx);
	mlx_loop(mlx->mlx_ptr);
}
