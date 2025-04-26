/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:06:03 by alphbarr          #+#    #+#             */
/*   Updated: 2025/04/26 21:07:51 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	ft_init_mlx(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		ft_error("Failed to initialize mlx");
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIDTH, HEIGHT, "miniRT");
	if (!mlx->win_ptr)
	{
		free(mlx->mlx_ptr);
		ft_error("Failed to create window");
	}
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);
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
