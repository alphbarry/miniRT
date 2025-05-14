#include "../../inc/minirt.h"

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
