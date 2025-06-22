/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_scene_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgomez-z <cgomez-z@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 23:26:01 by cgomez-z          #+#    #+#             */
/*   Updated: 2025/06/22 23:46:31 by cgomez-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	parse_error(char *msg, char *value)
{
	printf("Error: %s -> '%s'\n", msg, value);
	exit(EXIT_FAILURE);
}

static void	process_scene_line(char *ptr, int *has_a, int *has_c, int *has_l)
{
	if (ptr[0] == 'A' && (ptr[1] == ' ' || ptr[1] == '\t'))
		(*has_a)++;
	else if (ptr[0] == 'C' && (ptr[1] == ' ' || ptr[1] == '\t'))
		(*has_c)++;
	else if (ptr[0] == 'L' && (ptr[1] == ' ' || ptr[1] == '\t'))
		(*has_l)++;
}

static void	check_scene_counts(int has_a, int has_c, int fd)
{
	if (has_a > 1 || has_c > 1)
	{
		fprintf(stderr, "Error: Scene must contain 1 ambient, 1 camera\n");
		close(fd);
		exit(1);
	}
}

int	count_scene(t_scene *scene, int fd)
{
	char	*line;
	char	*ptr;
	int		has_a;
	int		has_c;
	int		has_l;

	has_a = 0;
	has_c = 0;
	has_l = 0;
	line = get_next_line(fd);
	while (line)
	{
		ptr = skip_spaces(line);
		if (*ptr != '\n' && *ptr != '#' && *ptr != '\0')
			process_scene_line(ptr, &has_a, &has_c, &has_l);
		free(line);
		line = get_next_line(fd);
	}
	check_scene_counts(has_a, has_c, fd);
	scene->general_count = has_a + has_c + has_l;
	return (scene->general_count);
}

void	parse_scene_from_file(char *file, t_scene *scene)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("Error reopening file for object count");
		exit(1);
	}
	init_scene(scene);
	count_objects(scene, fd);
	close(fd);
	allocate_objects(scene);
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("Error reopening file for scene parsing");
		exit(1);
	}
	get_scene(scene, fd);
	close(fd);
}
