/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpha <alpha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:37:41 by alpha             #+#    #+#             */
/*   Updated: 2025/05/08 20:59:44 by alpha            ###   ########.fr       */
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



int	read_file(char *file, t_scene *scene, t_mlx *mlx);

void	ft_error(char *message);

void	ft_init_mlx(t_mlx *mlx);

void	free_split(char **split);

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
t_vector	get_ray_direction(t_camera *camera, t_mlx *mlx, float x, float y);
void		set_pixel(t_mlx *mlx, t_color color, int x, int y);
int			intersect_sphere(t_vector origin, t_vector direction, t_sphere sphere, float *t);

//rendering
void	draw_sphere(t_mlx *mlx, t_sphere sphere, t_camera camera);
void	draw_scene(t_mlx *mlx, t_scene *scene);
#endif

