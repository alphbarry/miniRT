/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:06:03 by alphbarr          #+#    #+#             */
/*   Updated: 2025/04/27 21:42:46 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void init_mlx(t_mlx *mlx)
{
    mlx->mlx_ptr = NULL;
    mlx->win_ptr = NULL;
    mlx->img_ptr = NULL;
    mlx->img_data = NULL;
    mlx->bpp = 0;
    mlx->size_line = 0;
    mlx->endian = 0;
	mlx->win_x = 1920;
	mlx->win_y = 1080;
	mlx->shift_x = mlx->win_x / 2;
	mlx->shift_y = mlx->win_y / 2;
}


void	ft_init_mlx(t_mlx *mlx)
{
	init_mlx(mlx);
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		ft_error("Failed to initialize mlx");
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, 1920, 1080, "miniRT");
	if (!mlx->win_ptr)
	{
		free(mlx->mlx_ptr);
		ft_error("Failed to create window");
	}
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, 1920, 1080);
	if (!mlx->img_ptr)
	{
		free(mlx->win_ptr);
		free(mlx->mlx_ptr);
		ft_error("Failed to create image");
	}
	mlx->img_data = mlx_get_data_addr(mlx->img_ptr, &mlx->bpp,
			&mlx->size_line, &mlx->endian);
	if (!mlx->img_data)
	{
		free(mlx->img_ptr);
		free(mlx->win_ptr);
		free(mlx->mlx_ptr);
		ft_error("Failed to get image data address");
	}
}

int	ft_close_window(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr);
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx_destroy_display(mlx->mlx_ptr);
	free(mlx->mlx_ptr);
	exit(0);
}

void	full_screen(t_mlx *mlx)
{
	int	old_x;
	int	old_y;

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
