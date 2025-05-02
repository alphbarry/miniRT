/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpha <alpha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:37:41 by alpha             #+#    #+#             */
/*   Updated: 2025/04/27 21:55:18 by alphbarr         ###   ########.fr       */
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

int	read_file(char *file);

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

int	ft_close_window(t_mlx *mlx);

#endif

