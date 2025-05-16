/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpha <alpha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:37:41 by alpha             #+#    #+#             */
/*   Updated: 2025/05/16 19:45:16 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "./struct.h"
# include "../lib/mlx_linux/mlx.h"
# include "../lib/libft/src/libft.h"
# include "../lib/gnl/get_next_line.h"

int	key_hook(int keycode, t_scene *scene, t_mlx *mlx);

//parse
int		read_file(char *file, t_scene *scene, t_mlx *mlx);
void	get_ambient(t_scene *scene, char *line);
void	get_camera(t_scene *scene, char *line);
void	get_light(t_scene *scene, char *line);
void	get_sphere(t_scene *scene, char *line);
void	get_cylinder(t_scene *scene, char *line);
void	get_plane(t_scene *scene, char *line);

void	ft_error(char *message);

void	ft_init_mlx(t_mlx *mlx);

//free
void	free_split(char **split);
void	free_scene(t_scene *scene);

int	parse_error(char *msg, char *value);

//inits
void init_vector(t_vector *v);
void init_color(t_color *c);
void init_ray(t_ray *r);
void init_camera(t_camera *cam);
void init_sphere(t_sphere *sp);
void init_plane(t_plane *pl);
void init_cylinder(t_cylinder *cy);
void init_light(t_light *light);
void init_ambient(t_ambient *ambient);
void init_scene(t_scene *scene);
void init_mlx(t_mlx *mlx);
void init_data(t_data *data);


//mlx
int		ft_close_window(t_mlx *mlx);
void	update_window(int key, t_mlx *mlx);
int		deal_key(int key, t_mlx *mlx);
void	print_menu(t_mlx *param);

//colors
int		create_rgb(int r, int g, int b);
void	fill_background(t_mlx *mlx, t_scene *scene);
int		color_to_int(t_color color);
void		put_pixel(t_mlx *mlx, int x, int y, int color);

//vectors
t_vector	vector_add(t_vector a, t_vector b);
t_vector	vector_sub(t_vector a, t_vector b);
t_vector	vector_scale(t_vector a, float b);
t_vector	vector_normalize(t_vector a);
float		vector_dot(t_vector a, t_vector b);
t_vector	vector_cross(t_vector a, t_vector b);
float		vector_length(t_vector a);
t_vector	get_ray_direction(t_camera *camera, t_mlx *mlx, float x, float y);
void		set_pixel(t_mlx *mlx, t_color color, int x, int y);
int			intersect_sphere(t_vector origin, t_vector direction, t_sphere sphere, float *t);
int			intersect_plane(t_vector origin, t_vector direction, t_plane plane, float *t);
int			intersect_cylinder(t_vector origin, t_vector direction, t_cylinder cylinder, float *t);

//environment
t_color	compute_lighting(t_scene *scene, t_vector point, t_vector normal, t_color object_color);

//rendering
void	draw_sphere(t_mlx *mlx, t_scene *scene, t_sphere sphere);
void	draw_plane(t_mlx *mlx, t_scene *scene, t_plane plane);
void	draw_scene(t_mlx *mlx, t_scene *scene);

#endif

