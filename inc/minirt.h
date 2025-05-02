/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpha <alpha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:37:41 by alpha             #+#    #+#             */
/*   Updated: 2025/05/02 19:48:41 by alphbarr         ###   ########.fr       */
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


//mlx
int		ft_close_window(t_mlx *mlx);
void	update_window(int key, t_mlx *mlx);
int		deal_key(int key, t_mlx *mlx);
void	print_menu(t_mlx *param);

#endif

