/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 21:13:50 by alphbarr          #+#    #+#             */
/*   Updated: 2025/05/07 20:15:19 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	get_ambient(t_scene *scene, char *line)
{
	char	**split;
	char	**rgb;

	split = ft_split(line, ' ');
	if (!split)
		parse_error("Split failed", line);
	init_ambient(&scene->ambient);
	if (split[1])
	{
		scene->ambient.ratio = ft_atoif(split[1]);
		if (scene->ambient.ratio < 0 || scene->ambient.ratio > 1)
			parse_error("Ambient ratio out of range", split[1]);
	}
	else
		parse_error("Ambient ratio missing", line);
	if (split[2])
	{
		rgb = ft_split(split[2], ',');
		if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
			parse_error("One of rgb missing", split[2]);
		scene->ambient.color.r = ft_atoi(rgb[0]);
		scene->ambient.color.g = ft_atoi(rgb[1]);
		scene->ambient.color.b = ft_atoi(rgb[2]);
		if (scene->ambient.color.r < 0 || scene->ambient.color.r > 255)
			parse_error("Red value out of range", rgb[0]);
		if (scene->ambient.color.g < 0 || scene->ambient.color.g > 255)
			parse_error("Green value out of range", rgb[1]);
		if (scene->ambient.color.b < 0 || scene->ambient.color.b > 255)
			parse_error("Blue value out of range", rgb[2]);
		free_split(rgb);
	}
	else
		parse_error("Ambient color missing", line);
	free_split(split);
}

void	get_camera(t_scene *scene, char *line)
{
	char	**split;
	char	**pos;
	char	**trid;

	split = ft_split(line, ' ');
	if (!split)
		parse_error("Split failed", line);
	init_camera(&scene->camera);
	if (split[1])
	{
		pos = ft_split(split[1], ',');
		if (!pos || !pos[0] || !pos[1] || !pos[2])
			parse_error("Invalid camera position", split[1]);
		scene->camera.position.x = ft_atoif(pos[0]);
		scene->camera.position.y = ft_atoif(pos[1]);
		scene->camera.position.z = ft_atoif(pos[2]);
		free_split(pos);
	}
	else
		parse_error("Camera position missing", line);
	if (split[2])
	{
		trid = ft_split(split[2], ',');
		if (!trid || !trid[0] || !trid[1] || !trid[2])
			parse_error("Invalid camera orientation", split[2]);
		scene->camera.tridimensional.x = ft_atoif(trid[0]);
		scene->camera.tridimensional.y = ft_atoif(trid[1]);
		scene->camera.tridimensional.z = ft_atoif(trid[2]);
		free_split(trid);
	}
	else
		parse_error("Camera orientation missing", line);
	if (split[3])
		scene->camera.fov = ft_atoi(split[3]);
	else
		parse_error("Camera FOV missing", line);
	if (scene->camera.fov < 0 || scene->camera.fov > 180)
		parse_error("Camera FOV out of range", split[3]);
	free_split(split);
}

void	get_light(t_scene *scene, char *line)
{
	char	**split;
	char	**pos;
	char	**rgb;

	split = ft_split(line, ' ');
	if (!split)
		parse_error("Split failed", line);
	scene->lights = malloc(sizeof(t_light));
	init_light(scene->lights);
	if (split[1])
	{
		pos = ft_split(split[1], ',');
		if (!pos || !pos[0] || !pos[1] || !pos[2])
			parse_error("Invalid light position", split[1]);
		scene->lights->position.x = ft_atoif(pos[0]);
		scene->lights->position.y = ft_atoif(pos[1]);
		scene->lights->position.z = ft_atoif(pos[2]);
		free_split(pos);
	}
	else
		parse_error("Light position missing", line);
	if (split[2])
		scene->lights->intensity = ft_atoif(split[2]);
	else
		parse_error("Light intensity missing", line);
	if (scene->lights->intensity < 0 || scene->lights->intensity > 1)
		parse_error("Light intensity out of range", split[2]);
	if (split[3])
	{
		rgb = ft_split(split[3], ',');
		if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
			parse_error("Invalid light color", split[3]);
		scene->lights->color.r = ft_atoi(rgb[0]);
		scene->lights->color.g = ft_atoi(rgb[1]);
		scene->lights->color.b = ft_atoi(rgb[2]);
		if (scene->lights->color.r < 0 || scene->lights->color.r > 255)
			parse_error("Light red value out of range", rgb[0]);
		if (scene->lights->color.g < 0 || scene->lights->color.g > 255)
			parse_error("Light green value out of range", rgb[1]);
		if (scene->lights->color.b < 0 || scene->lights->color.b > 255)
			parse_error("Light blue value out of range", rgb[2]);
		free_split(rgb);
	}
	else
		parse_error("Light color missing", line);
	free_split(split);
}

void	get_sphere(t_scene *scene, char *line)
{
    char	**split;
    char	**pos;
    char	**rgb;
    t_sphere	new_sphere;

    split = ft_split(line, ' ');
    if (!split)
        parse_error("Split failed", line);
    // Procesa la posición de la esfera
    if (split[1])
    {
        pos = ft_split(split[1], ',');
        if (!pos || !pos[0] || !pos[1] || !pos[2])
            parse_error("Invalid sphere position", split[1]);
        new_sphere.center.x = ft_atoif(pos[0]);
        new_sphere.center.y = ft_atoif(pos[1]);
        new_sphere.center.z = ft_atoif(pos[2]);
        free_split(pos);
    }
    else
        parse_error("Sphere position missing", line);
    if (split[2])
        new_sphere.radius = ft_atoif(split[2]);
    else
        parse_error("Sphere radius missing", line);
    if (new_sphere.radius <= 0)
        parse_error("Sphere radius must be positive", split[2]);
    if (split[3])
    {
        rgb = ft_split(split[3], ',');
        if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
            parse_error("Invalid sphere color", split[3]);
        new_sphere.color.r = ft_atoi(rgb[0]);
        new_sphere.color.g = ft_atoi(rgb[1]);
        new_sphere.color.b = ft_atoi(rgb[2]);
        if (new_sphere.color.r < 0 || new_sphere.color.r > 255)
            parse_error("Sphere red value out of range", rgb[0]);
        if (new_sphere.color.g < 0 || new_sphere.color.g > 255)
            parse_error("Sphere green value out of range", rgb[1]);
        if (new_sphere.color.b < 0 || new_sphere.color.b > 255)
            parse_error("Sphere blue value out of range", rgb[2]);
        free_split(rgb);
    }
    else
        parse_error("Sphere color missing", line);
    // Añadir la esfera a la escena
    // Redimensionamos el array de esferas si es necesario
    scene->sphere_count++;
    scene->spheres = realloc(scene->spheres, scene->sphere_count * sizeof(t_sphere));
    if (!scene->spheres)
        parse_error("Memory allocation failed for spheres", NULL);
    scene->spheres[scene->sphere_count - 1] = new_sphere;
    free_split(split);
}


void	get_plane(t_scene *scene, char *line)
{
	char	**split;
	char	**pos;
	char	**trid;
	char	**rgb;

	split = ft_split(line, ' ');
	if (!split)
		parse_error("Split failed", line);
	scene->planes = malloc(sizeof(t_plane));
	init_plane(scene->planes);
	if (split[1])
	{
		pos = ft_split(split[1], ',');
		if (!pos || !pos[0] || !pos[1] || !pos[2])
			parse_error("Invalid plane position", split[1]);
		scene->planes->point.x = ft_atoif(pos[0]);
		scene->planes->point.y = ft_atoif(pos[1]);
		scene->planes->point.z = ft_atoif(pos[2]);
		free_split(pos);
	}
	else
		parse_error("Plane position missing", line);
	if (split[2])
	{
		trid = ft_split(split[2], ',');
		if (!trid || !trid[0] || !trid[1] || !trid[2])
			parse_error("Invalid plane normal", split[2]);
		scene->planes->tridimensional.x = ft_atoif(trid[0]);
		scene->planes->tridimensional.y = ft_atoif(trid[1]);
		scene->planes->tridimensional.z = ft_atoif(trid[2]);
		free_split(trid);
	}
	else
		parse_error("Plane normal missing", line);
	if (split[3])
	{
		rgb = ft_split(split[3], ',');
		if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
			parse_error("Invalid plane color", split[3]);
		scene->planes->color.r = ft_atoi(rgb[0]);
		scene->planes->color.g = ft_atoi(rgb[1]);
		scene->planes->color.b = ft_atoi(rgb[2]);
		if (scene->planes->color.r < 0 || scene->planes->color.r > 255)
			parse_error("Plane red value out of range", rgb[0]);
		if (scene->planes->color.g < 0 || scene->planes->color.g > 255)
			parse_error("Plane green value out of range", rgb[1]);
		if (scene->planes->color.b < 0 || scene->planes->color.b > 255)
			parse_error("Plane blue value out of range", rgb[2]);
		free_split(rgb);
	}
	else
		parse_error("Plane color missing", line);
	free_split(split);
}

void	get_cylinder(t_scene *scene, char *line)
{
	char	**split;
	char	**pos;
	char	**trid;
	char	**rgb;

	split = ft_split(line, ' ');
	if (!split)
		parse_error("Split failed", line);
	scene->cylinders = malloc(sizeof(t_cylinder));
	init_cylinder(scene->cylinders);
	if (split[1])
	{
		pos = ft_split(split[1], ',');
		if (!pos || !pos[0] || !pos[1] || !pos[2])
			parse_error("Invalid cylinder position", split[1]);
		scene->cylinders->center.x = ft_atoif(pos[0]);
		scene->cylinders->center.y = ft_atoif(pos[1]);
		scene->cylinders->center.z = ft_atoif(pos[2]);
		free_split(pos);
	}
	else
		parse_error("Cylinder position missing", line);
	if (split[2])
	{
		trid = ft_split(split[2], ',');
		if (!trid || !trid[0] || !trid[1] || !trid[2])
			parse_error("Invalid cylinder orientation", split[2]);
		scene->cylinders->tridimensional.x = ft_atoif(trid[0]);
		scene->cylinders->tridimensional.y = ft_atoif(trid[1]);
		scene->cylinders->tridimensional.z = ft_atoif(trid[2]);
		free_split(trid);
	}
	else
		parse_error("Cylinder orientation missing", line);
	if (split[3])
		scene->cylinders->radius = ft_atoif(split[3]);
	else
		parse_error("Cylinder radius missing", line);
	if (split[4])
		scene->cylinders->height = ft_atoif(split[4]);
	else
		parse_error("Cylinder height missing", line);
	if (split[5])
	{
		rgb = ft_split(split[5], ',');
		if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
			parse_error("Invalid cylinder color", split[5]);
		scene->cylinders->color.r = ft_atoi(rgb[0]);
		scene->cylinders->color.g = ft_atoi(rgb[1]);
		scene->cylinders->color.b = ft_atoi(rgb[2]);
		if (scene->cylinders->color.r < 0 || scene->cylinders->color.r > 255)
			parse_error("Cylinder red value out of range", rgb[0]);
		if (scene->cylinders->color.g < 0 || scene->cylinders->color.g > 255)
			parse_error("Cylinder green value out of range", rgb[1]);
		if (scene->cylinders->color.b < 0 || scene->cylinders->color.b > 255)
			parse_error("Cylinder blue value out of range", rgb[2]);
		free_split(rgb);
	}
	else
		parse_error("Cylinder color missing", line);
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
			printf("Unknown identifier\n");
		free(line);
		line = get_next_line(fd);
	}
}

int	read_file(char *file, t_scene *scene, t_mlx *mlx)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (1);
	}
	init_scene(scene);
	get_scene(scene, fd);
	close(fd);
	draw_scene(mlx, scene);
	return (0);
}
