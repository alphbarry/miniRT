 #include "../../inc/minirt.h"

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
	scene->light_count = 1;
	printf("DEBUG: Parsed light: pos(%.1f,%.1f,%.1f) intensity(%.1f) color(%d,%d,%d)\n",
		scene->lights->position.x,
		scene->lights->position.y,
		scene->lights->position.z,
		scene->lights->intensity,
		scene->lights->color.r,
		scene->lights->color.g,
		scene->lights->color.b);
	free_split(split);
}
