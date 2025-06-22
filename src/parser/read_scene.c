/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 21:13:50 by alphbarr          #+#    #+#             */
/*   Updated: 2025/06/22 23:41:33 by cgomez-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

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

static void	open_and_validate(char *file, t_scene *scene)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0 || count_scene(scene, fd) < 3)
	{
		close(fd);
		fprintf(stderr,
			"Error: Scene must contain 1 ambient, "
			"1 camera, and at least 1 light\n");
		exit(1);
	}
	close(fd);
}

int	read_file(char *file, t_scene *scene, t_mlx *mlx)
{
	open_and_validate(file, scene);
	parse_scene_from_file(file, scene);
	draw_scene(mlx, scene);
	return (0);
}
