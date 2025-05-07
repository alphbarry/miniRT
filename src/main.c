/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:55:49 by alphbarr          #+#    #+#             */
/*   Updated: 2025/05/07 20:14:56 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	ft_error(char *message)
{
	printf ("Error: %s\n", message);
}

int	main(int ac, char **av)
{
	t_mlx	mlx;
	t_scene	scene;

	(void)ac;
	ft_init_mlx(&mlx);
	read_file(av[1], &scene, &mlx);
	mlx_hook(mlx.win_ptr, 17, 0, ft_close_window, &mlx);
	mlx_key_hook(mlx.win_ptr, deal_key, &mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
