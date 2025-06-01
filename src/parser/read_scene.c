/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 21:13:50 by alphbarr          #+#    #+#             */
/*   Updated: 2025/06/02 00:36:06 by cgomez-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	parse_error(char *msg, char *value)
{
	printf("Error: %s -> '%s'\n", msg, value);
	exit(EXIT_FAILURE);
}

void	count_objects(t_scene *scene, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == '\n' || line[0] == '#')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (ft_strncmp(line, "L ", 2) == 0)
			scene->light_count++;
		else if (ft_strncmp(line, "sp ", 3) == 0)
			scene->sphere_count++;
		else if (ft_strncmp(line, "pl ", 3) == 0)
			scene->plane_count++;
		else if (ft_strncmp(line, "cy ", 3) == 0)
			scene->cylinder_count++;
		free(line);
		line = get_next_line(fd);
	}
}

static void	parse_line(t_scene *scene, char *line)
{
	if (ft_strncmp(line, "A ", 2) == 0)
		get_ambient(scene, line);
	else if (ft_strncmp(line, "C ", 2) == 0)
		get_camera(scene, line);
	else if (ft_strncmp(line, "L ", 2) == 0)
		get_light(scene, line);
	else if (ft_strncmp(line, "sp ", 3) == 0)
		get_sphere(scene, line);
	else if (ft_strncmp(line, "pl ", 3) == 0)
		get_plane(scene, line);
	else if (ft_strncmp(line, "cy ", 3) == 0)
		get_cylinder(scene, line);
	else
		printf("Unknown identifier\n");
}

void	get_scene(t_scene *scene, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == '\n' || line[0] == '#')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		parse_line(scene, line);
		free(line);
		line = get_next_line(fd);
	}
}

int	read_file(char *file, t_scene *scene, t_mlx *mlx)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (1);
	}
	init_scene(scene);
	count_objects(scene, fd);
	close(fd);
	allocate_objects(scene);
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (1);
	}
	get_scene(scene, fd);
	close(fd);
	draw_scene(mlx, scene);
	return (0);
}
