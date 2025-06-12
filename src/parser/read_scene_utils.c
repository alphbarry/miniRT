/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_scene_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgomez-z <cgomez-z@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 22:22:28 by cgomez-z          #+#    #+#             */
/*   Updated: 2025/06/12 19:07:50 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

char	*skip_spaces(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (line);
}

void	ft_error(char *message)
{
	printf("Error: %s\n", message);
	exit(1);
}

int	ft_dir(char *filename)
{
	if (!filename)
		return (0);
	if (ft_strncmp(filename, "scenes/", 7) != 0)
		return (0);
	if (filename[7] == '\0')
		return (0);
	return (1);
}

int	ft_extension_rt(char *filename, int fd)
{
	char	*dot;

	if (!ft_dir(filename))
	{
		close(fd);
		return (0);
	}
	dot = ft_strrchr(filename, '.');
	if (!dot || ft_strcmp(dot, ".rt") != 0)
	{
		close(fd);
		return (0);
	}
	return (1);
}
