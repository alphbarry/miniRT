/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:06:03 by alphbarr          #+#    #+#             */
/*   Updated: 2025/05/14 15:46:20 by alpha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void init_mlx(t_mlx *mlx)
{
    mlx->mlx_ptr = NULL;
    mlx->win_ptr = NULL;
    mlx->img_ptr = NULL;
    mlx->img_data = NULL;
    mlx->bpp = 0;
    mlx->size_line = 0;
    mlx->endian = 0;
   // mlx->win_x = 100;
   // mlx->win_y = 100;
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

void	print_menu(t_mlx *param)
{
	char	*menu;

	menu = "up, down, left, right: move picture";
	mlx_string_put(param->mlx_ptr, param->win_ptr, 10, 5, 0x03fc35, menu);
	menu = "5, space: 3d/2d mode; +, -: zoom";
	mlx_string_put(param->mlx_ptr, param->win_ptr, 10, 20, 0x03fc35, menu);
	menu = "8, 2: z-scale; 4, 6: rotation";
	mlx_string_put(param->mlx_ptr, param->win_ptr, 10, 35, 0x03fc35, menu);
}
