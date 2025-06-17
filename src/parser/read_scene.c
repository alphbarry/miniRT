/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 21:13:50 by alphbarr          #+#    #+#             */
/*   Updated: 2025/06/17 19:05:06 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	parse_error(char *msg, char *value)
{
	printf("Error: %s -> '%s'\n", msg, value);
	exit(EXIT_FAILURE);
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
		if (*ptr == '\n' || *ptr == '#' || *ptr == '\0')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (ptr[0] == 'A' && (ptr[1] == ' ' || ptr[1] == '\t'))
			has_a++;
		else if (ptr[0] == 'C' && (ptr[1] == ' ' || ptr[1] == '\t'))
			has_c++;
		else if (ptr[0] == 'L' && (ptr[1] == ' ' || ptr[1] == '\t'))
			has_l++;
		free(line);
		line = get_next_line(fd);
	}
	if (has_a > 1 || has_c > 1)
	{
		free(line);
		fprintf(stderr, "Error: Scene must contain 1 ambient, 1 camera\n");
		close(fd);
		exit(1);
	}
	scene->general_count = has_a + has_c + has_l;
	return (scene->general_count);
}

void	count_objects(t_scene *scene, int fd)
{
	char	*line;
	char	*ptr;

	line = get_next_line(fd);
	while (line)
	{
		ptr = skip_spaces(line);
		if (*ptr == '\n' || *ptr == '#' || *ptr == '\0')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (!ft_strncmp(ptr, "L", 1) && (ptr[1] == ' ' || ptr[1] == '\t'))
			scene->light_count++;
		else if (!ft_strncmp(ptr, "sp", 2) && (ptr[2] == ' ' || ptr[2] == '\t'))
			scene->sphere_count++;
		else if (!ft_strncmp(ptr, "pl", 2) && (ptr[2] == ' ' || ptr[2] == '\t'))
			scene->plane_count++;
		else if (!ft_strncmp(ptr, "cy", 2) && (ptr[2] == ' ' || ptr[2] == '\t'))
			scene->cylinder_count++;
		free(line);
		line = get_next_line(fd);
	}
}

static void	parse_line(t_scene *scene, char *line)
{
	char	*ptr;

	ptr = skip_spaces(line);
	if (!ft_strncmp(ptr, "A", 1) && (ptr[1] == ' ' || ptr[1] == '\t'))
		get_ambient(scene, ptr);
	else if (!ft_strncmp(ptr, "C", 1) && (ptr[1] == ' ' || ptr[1] == '\t'))
		get_camera(scene, ptr);
	else if (!ft_strncmp(ptr, "L", 1) && (ptr[1] == ' ' || ptr[1] == '\t'))
		get_light(scene, ptr);
	else if (!ft_strncmp(ptr, "sp", 2) && (ptr[2] == ' ' || ptr[2] == '\t'))
		get_sphere(scene, ptr);
	else if (!ft_strncmp(ptr, "pl", 2) && (ptr[2] == ' ' || ptr[2] == '\t'))
		get_plane(scene, ptr);
	else if (!ft_strncmp(ptr, "cy", 2) && (ptr[2] == ' ' || ptr[2] == '\t'))
		get_cylinder(scene, ptr);
	else
		parse_error("Unknown identifier", ptr);
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
	if (fd < 0 || count_scene(scene, fd) < 3)
	{
		close(fd);
		fprintf(stderr, "Error: Scene must contain 1 ambient, "
			"1 camera, and at least 1 light\n");
		exit(1);
	}
	close(fd);
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
	draw_scene(mlx, scene);
	return (0);
}
