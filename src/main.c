/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:55:49 by alphbarr          #+#    #+#             */
/*   Updated: 2025/06/09 14:45:11 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

int	main(int ac, char **av)
{
	t_mlx	mlx;
	t_scene	scene;

	if (ac < 2)
		ft_error("Usage: ./minirt <scene_file.rt>");
	else if (!ft_extension_rt(av[1], open(av[1], O_RDONLY)))
		ft_error("Invalid file extension. Expected .rt");
	ft_init_mlx(&mlx);
	read_file(av[1], &scene, &mlx);
	mlx_hook(mlx.win_ptr, 17, 0, ft_close_window, &mlx);
	mlx_key_hook(mlx.win_ptr, deal_key, &mlx);
	mlx_loop(mlx.mlx_ptr);
	free_scene(&scene);
	return (0);
}
