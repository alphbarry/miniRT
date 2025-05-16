#include "../../inc/minirt.h"

void	get_camera(t_scene *scene, char *line)
{
    char **split = ft_split(line, ' ');
    if (!validate_split(split, "Split failed", line))
        return;
    init_camera(&scene->camera);

    if (!split[1] || !parse_camera_position(&scene->camera, split[1]))
        return;
    if (!split[2] || !parse_camera_orientation(&scene->camera, split[2]))
        return;
    if (!split[3] || !parse_camera_fov(&scene->camera, split[3]))
        return;

    free_split(split);
}