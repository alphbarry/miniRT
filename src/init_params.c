/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 20:40:17 by alphbarr          #+#    #+#             */
/*   Updated: 2025/04/25 20:43:31 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void init_vector(t_vector *v)
{
    v->x = 0.0f;
    v->y = 0.0f;
    v->z = 0.0f;
}

void init_color(t_color *c)
{
    c->r = 0;
    c->g = 0;
    c->b = 0;
}

void init_ray(t_ray *r)
{
    init_vector(&r->origin);
    init_vector(&r->direction);
}

void init_camera(t_camera *cam)
{
    init_vector(&cam->position);
    init_vector(&cam->tridimensional);
    cam->fov = 0.0f;
}

void init_sphere(t_sphere *sp)
{
    init_vector(&sp->center);
    sp->radius = 0.0f;
    init_color(&sp->color);
}

void init_plane(t_plane *pl)
{
    init_vector(&pl->point);
    init_vector(&pl->tridimensional);
    init_color(&pl->color);
}

void init_cylinder(t_cylinder *cy)
{
    init_vector(&cy->center);
    init_vector(&cy->tridimensional);
    cy->radius = 0.0f;
    cy->height = 0.0f;
    init_color(&cy->color);
}

void init_light(t_light *light)
{
    init_vector(&light->position);
    light->intensity = 0.0f;
    init_color(&light->color);
}

void init_ambient(t_ambient *ambient)
{
    ambient->ratio = 0.0f;
    init_color(&ambient->color);
}

void init_scene(t_scene *scene)
{
    init_camera(&scene->camera);
    scene->spheres = NULL;
    scene->planes = NULL;
    scene->cylinders = NULL;
    scene->lights = NULL;
    init_ambient(&scene->ambient);
    scene->sphere_count = 0;
    scene->plane_count = 0;
    scene->cylinder_count = 0;
    scene->light_count = 0;
}

void init_mlx(t_mlx *mlx)
{
    mlx->mlx_ptr = NULL;
    mlx->win_ptr = NULL;
    mlx->img_ptr = NULL;
    mlx->img_data = NULL;
    mlx->bpp = 0;
    mlx->size_line = 0;
    mlx->endian = 0;
}

void init_data(t_data *data)
{
    init_mlx(&data->mlx);
    init_scene(&data->scene);
}
