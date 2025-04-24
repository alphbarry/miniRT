/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:20:22 by alphbarr          #+#    #+#             */
/*   Updated: 2025/04/24 19:53:37 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <math.h>
# include <fcntl.h>

typedef  struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_data;
	int		bpp;
	int		size_line;
	int		endian;
}	t_mlx;

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

typedef struct  s_color
{
	int		r;
	int		g;
	int		b;
}	t_color;


typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
}	t_ray;


typedef struct s_camara
{
	t_vector	position;
	t_vector	tridimensional;
	double		fov;
}	t_camera;

typedef struct s_sphere
{
	t_vector	center;
	double		radius;
	t_color		color;
}	t_sphere;

typedef struct s_plane
{
	t_vector	point;
	t_vector	tridimensional;
	t_color		color;
}	t_plane;

typedef struct s_cylinder
{
	t_vector	center;
	t_vector	tridimensional;
	double		radius;
	double		height;
	t_color		color;
}	t_cylinder;

typedef struct s_light
{
	t_vector	position;
	double		intensity;
}	t_light;

typedef struct s_ambient
{
	double		intensity;
	t_color		color;
}	t_ambient;

typedef struct s_scene
{
	t_camera		camera;
	t_sphere		*spheres;
	t_plane			*planes;
	t_cylinder		*cylinders;
	t_light			*lights;
	t_ambient		ambient;
	int				sphere_count;
	int				plane_count;
	int				cylinder_count;
	int				light_count;
}	t_scene;

typedef struct s_data
{
	t_mlx		mlx;
	t_scene		scene;
}	t_data;

#endif
