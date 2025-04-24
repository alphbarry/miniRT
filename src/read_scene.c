/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 21:13:50 by alphbarr          #+#    #+#             */
/*   Updated: 2025/04/24 21:58:14 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	get_ambient(t_scene *scene, char *line)
{
	char	**split;
	char	**rgb;
	
	split = ft_split(line, ' ');
	if (split[1])
		scene->ambient.ratio = ft_atoi(split[1]);
	if (split[2])
		{
			rgb = ft_split(split[2], ',');
			if (rgb[0] && rgb[1] && rgb[2])
			{
				scene->ambient.color.r = ft_atoi(rgb[0]);
				scene->ambient.color.g = ft_atoi(rgb[1]);
				scene->ambient.color.b = ft_atoi(rgb[2]);
			}
			free_split(rgb);
		}
	free_split(split);
}

void	get_camera(t_scene *scene, char *line)
{
	char	**split;
	char	**pos;
	char	**trid;

	split = ft_split(line, ' ');
	if (split[1])
	{
		pos = ft_split(split[1], ',');
		if (pos[0] && pos[1] && pos[2])
		{
			scene->camera.position.x = ft_atoi(pos[0]);
			scene->camera.position.y = ft_atoi(pos[1]);
			scene->camera.position.z = ft_atoi(pos[2]);
		}
		free_split(pos);
	}
	if (split[2])
	{
		trid = ft_split(split[2], ',');
		if (trid[0] && trid[1] && trid[2])
		{
			scene->camera.tridimensional.x = ft_atoi(trid[0]);
			scene->camera.tridimensional.y = ft_atoi(trid[1]);
			scene->camera.tridimensional.z = ft_atoi(trid[2]);
		}
		free_split(trid);
	}
	if (split[3])
		scene->camera.fov = ft_atoi(split[3]);
	free_split(split);
}


void	get_light(t_scene *scene, char *line)
{
	char	**split;
	char	**pos;
	char	**rgb;

	split = ft_split(line, ' ');
	if (split[1])
	{
		pos = ft_split(split[1], ',');
		if (pos[0] && pos[1] && pos[2])
		{
			scene->lights->position.x = ft_atoi(pos[0]);
			scene->lights->position.y = ft_atoi(pos[1]);
			scene->lights->position.z = ft_atoi(pos[2]);
		}
		free_split(pos);
	}
	if (split[2])
		scene->lights->intensity = ft_atoi(split[2]);
	if (split[3])
	{
		rgb = ft_split(split[3], ',');
		if (rgb[0] && rgb[1] && rgb[2])
		{
			scene->lights->color.r = ft_atoi(rgb[0]);
			scene->lights->color.g = ft_atoi(rgb[1]);
			scene->lights->color.b = ft_atoi(rgb[2]);
		}
		free_split(rgb);
	}
}

void	get_sphere(t_scene *scene, char *line)
{
	char	**split;
	char	**pos;
	char	**rgb;

	split = ft_split(line, ' ');
	if (split[1])
	{
		pos = ft_split(split[1], ',');
		if (pos[0] && pos[1] && pos[2])
		{
			scene->spheres->center.x = ft_atoi(pos[0]);
			scene->spheres->center.y = ft_atoi(pos[1]);
			scene->spheres->center.z = ft_atoi(pos[2]);
		}
		free_split(pos);
	}
	if (split[2])
		scene->spheres->radius = ft_atoi(split[2]);
	if (split[3])
	{
		rgb = ft_split(split[3], ',');
		if (rgb[0] && rgb[1] && rgb[2])
		{
			scene->spheres->color.r = ft_atoi(rgb[0]);
			scene->spheres->color.g = ft_atoi(rgb[1]);
			scene->spheres->color.b = ft_atoi(rgb[2]);
		}
		free_split(rgb);
	}
	free_split(split);
}

void	get_plane(t_scene *scene, char *line)
{
	char	**split;
	char	**pos;
	char	**trid;
	char	**rgb;

	split = ft_split(line, ' ');
	if (split[1])
	{
		pos = ft_split(split[1], ',');
		if (pos[0] && pos[1] && pos[2])
		{
			scene->planes->point.x = ft_atoi(pos[0]);
			scene->planes->point.y = ft_atoi(pos[1]);
			scene->planes->point.z = ft_atoi(pos[2]);
		}
		free_split(pos);
	}
	if (split[2])
	{
		trid = ft_split(split[2], ',');
		if (trid[0] && trid[1] && trid[2])
		{
			scene->planes->tridimensional.x = ft_atoi(trid[0]);
			scene->planes->tridimensional.y = ft_atoi(trid[1]);
			scene->planes->tridimensional.z = ft_atoi(trid[2]);
		}
		free_split(trid);
	}
	if (split[3])
	{
		rgb = ft_split(split[3], ',');
		if (rgb[0] && rgb[1] && rgb[2])
		{
			scene->planes->color.r = ft_atoi(rgb[0]);
			scene->planes->color.g = ft_atoi(rgb[1]);
			scene->planes->color.b = ft_atoi(rgb[2]);
		}
		free_split(rgb);
	}
	free_split(split);
}

void	get_cylinder(t_scene *scene, char *line)
{
	char	**split;
	char	**pos;
	char	**trid;
	char	**rgb;

	split = ft_split(line, ' ');
	if (split[1])
	{
		pos = ft_split(split[1], ',');
		if (pos[0] && pos[1] && pos[2])
		{
			scene->cylinders->center.x = ft_atoi(pos[0]);
			scene->cylinders->center.y = ft_atoi(pos[1]);
			scene->cylinders->center.z = ft_atoi(pos[2]);
		}
		free_split(pos);
	}
	if (split[2])
	{
		trid = ft_split(split[2], ',');
		if (trid[0] && trid[1] && trid[2])
		{
			scene->cylinders->tridimensional.x = ft_atoi(trid[0]);
			scene->cylinders->tridimensional.y = ft_atoi(trid[1]);
			scene->cylinders->tridimensional.z = ft_atoi(trid[2]);
		}
		free_split(trid);
	}
	if (split[3])
		scene->cylinders->radius = ft_atoi(split[3]);
	if (split[4])
		scene->cylinders->height = ft_atoi(split[4]);
	if (split[5])
	{
		rgb = ft_split(split[5], ',');
		if (rgb[0] && rgb[1] && rgb[2])
		{
			scene->cylinders->color.r = ft_atoi(rgb[0]);
			scene->cylinders->color.g = ft_atoi(rgb[1]);
			scene->cylinders->color.b = ft_atoi(rgb[2]);
		}
		free_split(rgb);
	}
	free_split(split);
}

void	get_scene(t_scene *scene, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
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
			printf("Unknown identifier: %s\n", line);
		free(line);
	}
	close(fd);
}

void	init_scene(t_scene *scene)
{
	scene->ambient.ratio = 0;
	scene->camera.fov = 0;
	scene->lights = NULL;
	scene->spheres = NULL;
	scene->planes = NULL;
	scene->cylinders = NULL;
}

void	**read_file(char *file)
{
	int		fd;
	t_scene	scene;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (NULL);
	}
	init_scene(&scene);
	get_scene(&scene, fd);
	return (NULL);
}
