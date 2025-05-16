#include "../../inc/minirt.h"

void	get_light(t_scene *scene, char *line)
{
	char	**split;

	split = ft_split(line, ' ');
	if (!validate_split(split, "Split failed", line))
		return;
	scene->lights = set_light_properties();
	if (split[1])
		parse_light_position(scene->lights, split[1]);
	else
		parse_error("Light position missing", line);
	
	if (!parse_light_intensity(scene->lights, split[2]))
		return;
	
	if (!parse_light_color(scene->lights, split[3]))
		return;
	
	scene->light_count++;
	free_split(split);
}
