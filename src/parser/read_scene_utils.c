/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_scene_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgomez-z <cgomez-z@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 22:22:28 by cgomez-z          #+#    #+#             */
/*   Updated: 2025/06/07 14:40:57 by alpha            ###   ########.fr       */
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
	printf ("Error: %s\n", message);
	exit(1);
}

int	ft_extension_rt(char *filename, int fd)
{
	char	*dot;

	dot = ft_strrchr(filename, '.');
	if (!dot || ft_strncmp(dot, ".rt", 3) != 0)
	{
		close(fd);
		return (0);
	}
	return (1);
}
