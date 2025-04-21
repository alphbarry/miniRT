/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpha <alpha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:37:41 by alpha             #+#    #+#             */
/*   Updated: 2025/04/21 20:31:19 by alpha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include "../lib/mlx_linux/mlx.h"
# include "../lib/libft/src/libft.h"
# include "../lib/gnl/get_next_line.h"

# define WIDTH 800
# define HEIGHT 600
# define EPSILON 0.0001
# define MAX_DISTANCE 1000.0
# define MAX_OBJECTS 100
# define MAX_LIGHTS 10

/*
** Vector structure for 3D coordinates and colors
*/

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

/*
** Ray structure
*/

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	dir;
}	t_ray;

/*
** Camera structure
*/

typedef struct s_camera
{
	t_vec3	position;
	t_vec3	direction;
	t_vec3	up;
	t_vec3	right;
	double	fov;
	double	aspect_ratio;
}	t_camera;

/*
** Object types enumeration
*/

typedef enum e_object_type
{
	SPHERE,
	PLANE,
	CYLINDER
}	t_object_type;

/*
** Sphere structure
*/

typedef struct s_sphere
{
	t_vec3	center;
	double	radius;
	t_vec3	color;
}	t_sphere;

/*
** Plane structure
*/

typedef struct s_plane
{
	t_vec3	point;
	t_vec3	normal;
	t_vec3	color;
}	t_plane;

/*
** Object structure (union of all possible objects)
*/

typedef struct s_object
{
	t_object_type	type;
	union
	{
		t_sphere	sphere;
		t_plane		plane;
	}	u;
}	t_object;

/*
** Light structures
*/

typedef struct s_ambient
{
	double	intensity;
	t_vec3	color;
}	t_ambient;

typedef struct s_light
{
	t_vec3	position;
	double	intensity;
	t_vec3	color;
}	t_light;

/*
** Scene structure to hold all objects and lights
*/

typedef struct s_scene
{
	t_camera	camera;
	t_ambient	ambient;
	t_light		lights[MAX_LIGHTS];
	int			light_count;
	t_object	objects[MAX_OBJECTS];
	int			object_count;
}	t_scene;

/*
** MLX data structure
*/

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_mlx;

/*
** Main program structure
*/

typedef struct s_program
{
	t_mlx	mlx;
	t_scene	scene;
}	t_program;

/*
** Intersection result structure
*/

typedef struct s_hit
{
	double	t;
	t_vec3	point;
	t_vec3	normal;
	t_vec3	color;
	int		hit;
}	t_hit;

/*
** Vector operations
*/

t_vec3		ft_vec3_create(double x, double y, double z);
t_vec3		ft_vec3_add(t_vec3 v1, t_vec3 v2);
t_vec3		ft_vec3_sub(t_vec3 v1, t_vec3 v2);
t_vec3		ft_vec3_mult(t_vec3 v, double t);
t_vec3		ft_vec3_div(t_vec3 v, double t);
double		ft_vec3_dot(t_vec3 v1, t_vec3 v2);
t_vec3		ft_vec3_cross(t_vec3 v1, t_vec3 v2);
double		ft_vec3_length(t_vec3 v);
t_vec3		ft_vec3_normalize(t_vec3 v);
t_vec3		ft_vec3_color_mult(t_vec3 c1, t_vec3 c2);
t_vec3	ft_vec3_clamp(t_vec3 v, double min, double max);

/*
** Ray operations
*/

t_ray		ft_ray_create(t_vec3 origin, t_vec3 direction);
t_vec3		ft_ray_at(t_ray ray, double t);

/*
** Intersection functions
*/

t_hit		ft_intersect_sphere(t_ray ray, t_sphere sphere);
t_hit		ft_intersect_plane(t_ray ray, t_plane plane);
t_hit		ft_intersect_scene(t_ray ray, t_scene scene);

/*
** Lighting functions
*/

t_vec3		ft_calculate_light(t_hit hit, t_scene scene);
int			ft_is_in_shadow(t_vec3 point, t_vec3 light_dir, double light_dist, 
				t_scene scene);

/*
** Rendering functions
*/

int		ft_render_scene(t_program *program);
t_vec3		ft_ray_color(t_ray ray, t_scene scene);

/*
** Initialization functions
*/

void		ft_init_camera(t_camera *camera, t_vec3 position, t_vec3 direction, 
				double fov);
int			ft_init_mlx(t_program *program);

/*
** Parsing functions
*/

int			ft_parse_scene(char *filename, t_scene *scene);
int			ft_parse_camera(char **tokens, t_scene *scene);
int			ft_parse_ambient(char **tokens, t_scene *scene);
int			ft_parse_light(char **tokens, t_scene *scene);
int			ft_parse_sphere(char **tokens, t_scene *scene);
int			ft_parse_plane(char **tokens, t_scene *scene);

/*
** Utility functions
*/

double		ft_atod(char *str);
char		**ft_split(char const *s, char c);
void		ft_free_split(char **split);
int			ft_error(char *message);

#endif

