/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpha <alpha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:37:41 by alpha             #+#    #+#             */
/*   Updated: 2025/04/21 20:23:07 by alpha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

/*
** Parse a 3D vector from a string (format: x,y,z)
*/

void	ft_free_split(char **splt)
{
    int	i;

    if (!splt)
        return;
    i = 0;
    while (splt[i])
    {
        free(splt[i]);
        i++;
    }
    free(splt);
}

int	ft_parse_vector(char *str, t_vec3 *vec)
{
	char	**parts;
	int		ret;

	ret = 0;
	parts = ft_split(str, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3])
		ret = ft_error("Invalid vector format, expected x,y,z");
	else
	{
		vec->x = ft_atod(parts[0]);
		vec->y = ft_atod(parts[1]);
		vec->z = ft_atod(parts[2]);
	}
	if (parts)
		ft_free_split(parts);
	return (ret);
}

/*
** Parse RGB color from a string (format: r,g,b)
** Values should be between 0 and 255
*/

int	ft_parse_color(char *str, t_vec3 *color)
{
	char	**parts;
	int		r;
	int		g;
	int		b;
	int		ret;

	ret = 0;
	parts = ft_split(str, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3])
		ret = ft_error("Invalid color format, expected r,g,b");
	else
	{
		r = atoi(parts[0]);
		g = atoi(parts[1]);
		b = atoi(parts[2]);
		if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
			ret = ft_error("Color values must be between 0 and 255");
		else
			*color = ft_vec3_create(r / 255.0, g / 255.0, b / 255.0);
	}
	if (parts)
		ft_free_split(parts);
	return (ret);
}

/*
** Parse ambient light (A ratio r,g,b)
*/

int	ft_parse_ambient(char **tokens, t_scene *scene)
{
	double	ratio;

	if (!tokens[1] || !tokens[2] || tokens[3])
		return (ft_error("Invalid ambient light format"));
	ratio = ft_atod(tokens[1]);
	if (ratio < 0.0 || ratio > 1.0)
		return (ft_error("Ambient light ratio must be between 0 and 1"));
	if (ft_parse_color(tokens[2], &scene->ambient.color))
		return (1);
	scene->ambient.intensity = ratio;
	return (0);
}

/*
** Parse camera (C x,y,z nx,ny,nz fov)
*/

int	ft_parse_camera(char **tokens, t_scene *scene)
{
	t_vec3	up;
	double	fov;

	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		return (ft_error("Invalid camera format"));
	if (ft_parse_vector(tokens[1], &scene->camera.position))
		return (1);
	if (ft_parse_vector(tokens[2], &scene->camera.direction))
		return (1);
	if (fabs(scene->camera.direction.x) < EPSILON && 
		fabs(scene->camera.direction.y) < EPSILON && 
		fabs(scene->camera.direction.z) < EPSILON)
		return (ft_error("Camera direction cannot be zero vector"));
	scene->camera.direction = ft_vec3_normalize(scene->camera.direction);
	fov = ft_atod(tokens[3]);
	if (fov <= 0.0 || fov >= 180.0)
		return (ft_error("Camera FOV must be between 0 and 180"));
	scene->camera.fov = fov;
	up = ft_vec3_create(0, 1, 0);
	if (fabs(ft_vec3_dot(up, scene->camera.direction)) > 0.9)
		up = ft_vec3_create(0, 0, 1);
	scene->camera.right = ft_vec3_normalize(
			ft_vec3_cross(scene->camera.direction, up));
	scene->camera.up = ft_vec3_normalize(
			ft_vec3_cross(scene->camera.right, scene->camera.direction));
	scene->camera.aspect_ratio = (double)WIDTH / (double)HEIGHT;
	return (0);
}

/*
** Parse light (L x,y,z brightness r,g,b)
*/

int	ft_parse_light(char **tokens, t_scene *scene)
{
	double	brightness;

	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		return (ft_error("Invalid light format"));
	if (scene->light_count >= MAX_LIGHTS)
		return (ft_error("Too many lights in scene"));
	if (ft_parse_vector(tokens[1], &scene->lights[scene->light_count].position))
		return (1);
	brightness = ft_atod(tokens[2]);
	if (brightness < 0.0 || brightness > 1.0)
		return (ft_error("Light brightness must be between 0 and 1"));
	if (ft_parse_color(tokens[3], &scene->lights[scene->light_count].color))
		return (1);
	scene->lights[scene->light_count].intensity = brightness;
	scene->light_count++;
	return (0);
}

/*
** Parse sphere (sp x,y,z diameter r,g,b)
*/

int	ft_parse_sphere(char **tokens, t_scene *scene)
{
	t_sphere	*sphere;
	double		diameter;

	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		return (ft_error("Invalid sphere format"));
	if (scene->object_count >= MAX_OBJECTS)
		return (ft_error("Too many objects in scene"));
	sphere = &scene->objects[scene->object_count].u.sphere;
	scene->objects[scene->object_count].type = SPHERE;
	if (ft_parse_vector(tokens[1], &sphere->center))
		return (1);
	diameter = ft_atod(tokens[2]);
	if (diameter <= 0.0)
		return (ft_error("Sphere diameter must be positive"));
	sphere->radius = diameter / 2.0;
	if (ft_parse_color(tokens[3], &sphere->color))
		return (1);
	scene->object_count++;
	return (0);
}

/*
** Parse plane (pl x,y,z nx,ny,nz r,g,b)
*/

int	ft_parse_plane(char **tokens, t_scene *scene)
{
	t_plane	*plane;

	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		return (ft_error("Invalid plane format"));
	if (scene->object_count >= MAX_OBJECTS)
		return (ft_error("Too many objects in scene"));
	plane = &scene->objects[scene->object_count].u.plane;
	scene->objects[scene->object_count].type = PLANE;
	if (ft_parse_vector(tokens[1], &plane->point))
		return (1);
	if (ft_parse_vector(tokens[2], &plane->normal))
		return (1);
	if (fabs(plane->normal.x) < EPSILON && 
		fabs(plane->normal.y) < EPSILON && 
		fabs(plane->normal.z) < EPSILON)
		return (ft_error("Plane normal cannot be zero vector"));
	plane->normal = ft_vec3_normalize(plane->normal);
	if (ft_parse_color(tokens[3], &plane->color))
		return (1);
	scene->object_count++;
	return (0);
}

/*
** Parse a line from the scene file
*/

int	ft_parse_line(char *line, t_scene *scene)
{
	char	**tokens;
	int		ret;

	ret = 0;
	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0])
		ret = 0;
	else if (tokens[0][0] == '#')
		ret = 0;
	else if (ft_strcmp(tokens[0], "A") == 0)
		ret = ft_parse_ambient(tokens, scene);
	else if (ft_strcmp(tokens[0], "C") == 0)
		ret = ft_parse_camera(tokens, scene);
	else if (ft_strcmp(tokens[0], "L") == 0)
		ret = ft_parse_light(tokens, scene);
	else if (ft_strcmp(tokens[0], "sp") == 0)
		ret = ft_parse_sphere(tokens, scene);
	else if (ft_strcmp(tokens[0], "pl") == 0)
		ret = ft_parse_plane(tokens, scene);
	else
		ret = ft_error("Unknown element type");
	if (tokens)
		ft_free_split(tokens);
	return (ret);
}

/*
** Initialize scene with default values
*/

void	ft_init_scene(t_scene *scene)
{
	scene->object_count = 0;
	scene->light_count = 0;
	scene->ambient.intensity = 0.1;
	scene->ambient.color = ft_vec3_create(1.0, 1.0, 1.0);
	scene->camera.position = ft_vec3_create(0.0, 0.0, 0.0);
	scene->camera.direction = ft_vec3_create(0.0, 0.0, -1.0);
	scene->camera.up = ft_vec3_create(0.0, 1.0, 0.0);
	scene->camera.right = ft_vec3_create(1.0, 0.0, 0.0);
	scene->camera.fov = 70.0;
	scene->camera.aspect_ratio = (double)WIDTH / (double)HEIGHT;
}

/*
** Read and parse a scene file
*/

int	ft_parse_scene(char *filename, t_scene *scene)
{
    int		fd;
    char	*line;
    int		ret;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (ft_error("Failed to open scene file"));
    ft_init_scene(scene);
    ret = 0;
    while ((line = get_next_line(fd)) != NULL && ret == 0)
    {
        ret = ft_parse_line(line, scene);
        free(line);
    }
    if (line == NULL && ret == 0) // Verificar si hubo un error en get_next_line
        ret = ft_error("Error reading scene file");
    close(fd);
    return (ret);
}

/*
** Convert string to double
*/

double	ft_atod(char *str)
{
	double	result;
	double	decimal;
	int		sign;
	int		i;

	result = 0.0;
	decimal = 0.0;
	sign = 1;
	i = 0;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		result = result * 10.0 + (str[i++] - '0');
	if (str[i] == '.')
	{
		i++;
		decimal = 0.1;
		while (str[i] >= '0' && str[i] <= '9')
		{
			result += (str[i++] - '0') * decimal;
			decimal *= 0.1;
		}
	}
	return (result * sign);
}

