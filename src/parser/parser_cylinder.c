#include "../../inc/minirt.h"

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
		scene->cylinders->normal.x = ft_atoif(trid[0]);
		scene->cylinders->normal.y = ft_atoif(trid[1]);
		scene->cylinders->normal.z = ft_atoif(trid[2]);
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
