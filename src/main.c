/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:55:49 by alphbarr          #+#    #+#             */
/*   Updated: 2025/04/26 21:06:59 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	ft_error(char *message)
{
	printf ("Error: %s\n", message);
}

int	main(int ac, char **av)
{
	(void)ac;
	read_file(av[1]);
	init_mlx();
	if (!mlx)
		return (ft_error("Failed to initialize mlx"));
	return (0);
}
