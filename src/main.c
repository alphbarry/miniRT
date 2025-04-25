/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:55:49 by alphbarr          #+#    #+#             */
/*   Updated: 2025/04/25 21:00:32 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

int	ft_error(char *message)
{
	printf ("Error: %s\n", message);
	return (1);
}

int	main(int ac, char **av)
{
	//t_data	data;

	if (ac != 2)
		return (ft_error("Usage: ./miniRT scene_file.rt"));
	if (ft_strncmp(av[1] + ft_strlen(av[1]) - 3, ".rt", 3) != 0)
		return (ft_error("File extension must be .rt"));
	read_file(av[1]);
	return (0);
}
