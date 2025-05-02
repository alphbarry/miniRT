/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:55:49 by alphbarr          #+#    #+#             */
/*   Updated: 2025/04/27 22:00:28 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	ft_error(char *message)
{
	printf ("Error: %s\n", message);
}


int	main(int ac, char **av)
{
	t_data data;
	t_mlx	*mlx;

	(void)ac;
	read_file(av[1]);
	mlx = malloc(sizeof(t_mlx));
	ft_init_mlx(mlx);
	if (!mlx)
		ft_error("Failed to initialize mlx");
	mlx_hook(mlx->win_ptr, 17, 0, ft_close_window, mlx);
	mlx_key_hook(mlx->win_ptr, deal_key, mlx);
	mlx_loop(mlx->mlx_ptr);
	return (0);
}
