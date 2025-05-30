/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgomez-z <cgomez-z@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:57:06 by cgomez-z          #+#    #+#             */
/*   Updated: 2025/05/30 01:55:20 by cgomez-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/* --- Chequeo de esferas --------------------------------------------------- */
static void	check_spheres(t_scene *sc, t_vector o, t_vector d, t_trace *tr)
{
	int		i;
	float	t;

	i = 0;
	while (i < sc->sphere_count)
	{
		if (intersect_sphere(o, d, sc->spheres[i], &t) && t < tr->closest_t)
		{
			tr->closest_t = t;
			tr->hit = vector_add(o, vector_scale(d, t));
			tr->normal = vector_normalize(
					vector_sub(tr->hit, sc->spheres[i].center));
			tr->color = compute_lighting(sc, tr->hit, tr->normal,
					sc->spheres[i].color);
		}
		i++;
	}
}

/* --- Chequeo de planos ---------------------------------------------------- */
static void	check_planes(t_scene *sc, t_vector o, t_vector d, t_trace *tr)
{
	int		i;
	float	t;

	i = 0;
	while (i < sc->plane_count)
	{
		if (intersect_plane(o, d, sc->planes[i], &t) && t < tr->closest_t)
		{
			tr->closest_t = t;
			tr->hit = vector_add(o, vector_scale(d, t));
			tr->normal = vector_normalize(sc->planes[i].normal);
			tr->color = compute_lighting(sc, tr->hit, tr->normal,
					sc->planes[i].color);
		}
		i++;
	}
}

/* --- Chequeo de cilindros -------------------------------------------------
static void	check_cylinders(t_scene *sc, t_vector o, t_vector d, t_trace *tr)
{
	int			i;
	float		t;
	float		proj;
	t_vector	tmp[2];

	i = 0;
	while (i < sc->cylinder_count)
	{
		if (intersect_cylinder(o, d, sc->cylinders[i], &t) && t < tr->closest_t)
		{
			tr->closest_t = t;
			tr->hit = vector_add(o, vector_scale(d, t));
			tmp[0] = vector_normalize(sc->cylinders[i].normal);
			tmp[1] = vector_sub(tr->hit, sc->cylinders[i].center);
			proj = vector_dot(tmp[1], tmp[0]);
			tmp[1] = vector_add(sc->cylinders[i].center,
					vector_scale(tmp[0], proj));
			tr->normal = vector_normalize(vector_sub(tr->hit, tmp[1]));
			tr->color = compute_lighting(sc, tr->hit, tr->normal,
					sc->cylinders[i].color);
		}
		i++;
	}
}
*/

static void	check_cylinders(t_scene *sc, t_vector o, t_vector d, t_trace *tr)
{
	int			i;
	float		t;
	t_pixel		px;
	t_cyhit		info;

	i = 0;
	while (i < sc->cylinder_count)
	{
		px.origin = o;
		px.direction = d;
		px.x = 0;
		px.y = 0;
		if (check_cylinder_hits(sc->cylinders[i], px, &t) && t < tr->closest_t)
		{
			info.origin = o;
			info.direction = d;
			info.t = t;
			info.scene = sc;
			update_trace_cylinder(tr, &sc->cylinders[i], info);
		}
		i++;
	}
}


/* --- Color de un píxel ----------------------------------------------------
static t_color	compute_pixel(t_scene *sc, t_mlx *mlx, t_vector o, int x, int y)
{
	t_trace		tr;
	t_vector	d;

	tr.closest_t = INFINITY;
	tr.color.r = 0;
	tr.color.g = 0;
	tr.color.b = 0;
	d = get_ray_direction(&sc->camera, mlx, (float)x, (float)y);
	check_spheres(sc, o, d, &tr);
	check_planes(sc, o, d, &tr);
	check_cylinders(sc, o, d, &tr);
	return (tr.color);
}*/

static t_color compute_pixel(t_scene *sc, t_mlx *mlx, int x, int y)
{
	t_trace		tr;
	t_vector	d;
	t_vector	o;

	o = sc->camera.position;
	tr.closest_t = INFINITY;
	tr.color = (t_color){0, 0, 0};
	d = get_ray_direction(&sc->camera, mlx, (float)x, (float)y);
	check_spheres(sc, o, d, &tr);
	check_planes(sc, o, d, &tr);
	check_cylinders(sc, o, d, &tr);
	return (tr.color);
}


/* --- Función principal de render ----------------------------------------- */
void	draw_scene(t_mlx *mlx, t_scene *sc)
{
	int			x;
	int			y;
	t_vector	o;
	t_color		c;

	fill_background(mlx, sc);
	o = sc->camera.position;
	y = 0;
	while (y < mlx->win_y)
	{
		x = 0;
		while (x < mlx->win_x)
		{
			c = compute_pixel(sc, mlx, x, y);
			set_pixel(mlx, c, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
}

