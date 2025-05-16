#include "../../inc/minirt.h"

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
	fprintf(stderr, "DEBUG: Parsed camera: pos(%.1f,%.1f,%.1f) dir(%.1f,%.1f,%.1f) fov(%.1f)\n",
		scene->camera.position.x,
		scene->camera.position.y,
		scene->camera.position.z,
		scene->camera.tridimensional.x,
		scene->camera.tridimensional.y,
		scene->camera.tridimensional.z,
		scene->camera.fov);
	free_split(split);
}
