#include "../../inc/minirt.h"

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
		scene->planes->normal.x = ft_atoif(trid[0]);
		scene->planes->normal.y = ft_atoif(trid[1]);
		scene->planes->normal.z = ft_atoif(trid[2]);
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
	scene->plane_count++;
	/*fprintf(stderr, "DEBUG: Parsed plane %d: point(%.1f,%.1f,%.1f) normal(%.1f,%.1f,%.1f)\n",
		scene->plane_count - 1,
		scene->planes->point.x, scene->planes->point.y, scene->planes->point.z,
		scene->planes->normal.x, scene->planes->normal.y, scene->planes->normal.z);*/
	free_split(split);
}
