/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:20:22 by alphbarr          #+#    #+#             */
/*   Updated: 2025/05/16 19:49:08 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <math.h>
# include <fcntl.h>

# define KEY_ESC 65307
# define KEY_8 65431
# define KEY_8T 56
# define KEY_2 65433
# define KEY_2T 50
# define KEY_4 65430
# define KEY_4T 52
# define KEY_6 65432
# define KEY_6T 54
# define KEY_PLUS 65451
# define KEY_PLUST 43
# define KEY_MINUS 65453
# define KEY_MINUST 45
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_5 65437
# define KEY_5T 53
# define KEY_SPACE 32
# define KEY_F 102

typedef  struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_data;
	int		bpp;
	int		size_line;
	int		endian;
	int		win_x;
	int		win_y;
	int		shift_x;
	int		shift_y;
}	t_mlx;

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
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
	float		fov;
}	t_camera;

typedef struct s_sphere
{
	t_vector	center;
	float		radius;
	t_color		color;
	struct s_sphere	*next;
}	t_sphere;

typedef struct s_plane
{
	t_vector	point;
	t_vector	normal;
	t_color		color;
	struct s_plane	*next;
}	t_plane;

typedef struct s_cylinder
{
	t_vector	center;
	t_vector	normal;
	float		radius;
	float		height;
	t_color		color;
	struct s_cylinder	*next;
}	t_cylinder;

typedef struct s_disk
{
	t_vector	center;
	t_vector	normal;
	float		radius;
}	t_disk;

typedef struct s_light
{
	t_vector	position;
	float		intensity;
	t_color		color;
	struct s_light	*next;
}	t_light;

typedef struct s_ambient
{
	float		ratio;
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
