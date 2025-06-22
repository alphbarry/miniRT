/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpha <alpha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:37:41 by alpha             #+#    #+#             */
/*   Updated: 2025/06/07 14:37:07 by alpha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../lib/gnl/get_next_line.h"
# include "../lib/libft/src/libft.h"
# include "../lib/mlx_linux/mlx.h"
# include "./struct.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/* Lighting calculation configuration */
# define LIGHT_INTENSITY_SCALE 2.0f
# define SHADOW_BIAS 0.001f
# define SPECULAR_SHININESS 80.0f
# define SPECULAR_INTENSITY 0.8f
# define AMBIENT_BOOST 0.15f

// Lighting calculation data structure
typedef struct s_lighting_data
{
	t_vector	point;
	t_vector	normal;
	t_vector	view_dir;
	t_color		object_color;
	t_color		final_color;
}				t_lighting_data;

int				key_hook(int keycode, t_scene *scene, t_mlx *mlx);

// parse
int				ft_extension_rt(char *filename, int fd);
char			*skip_spaces(char *line);
int				read_file(char *file, t_scene *scene, t_mlx *mlx);
void			get_ambient(t_scene *scene, char *line);
void			get_camera(t_scene *scene, char *line);
void			get_light(t_scene *scene, char *line);
void			get_sphere(t_scene *scene, char *line);
void			get_cylinder(t_scene *scene, char *line);
void			get_plane(t_scene *scene, char *line);
int				validate_coordinates(char **coords, char *err_msg, char *value);
int				validate_numeric_range(float value, float min, float max,
					char *err_msg);
int				validate_color_component(int value, char *component,
					char *err_msg);
int				validate_color_values(char **rgb, char *err_msg, char *value);
int				validate_split(char **split, char *err_msg, char *line);
void			parse_cylinder_position(t_cylinder *cylinder, char *pos_str);
void			parse_cylinder_orientation(t_cylinder *cylinder,
					char *orient_str);
int				parse_cylinder_dimensions(t_cylinder *cylinder,
					char *radius_str, char *height_str);
int				parse_cylinder_color(t_cylinder *cylinder, char *color_str);
t_cylinder		*set_cylinder_properties(void);
void			parse_plane_position(t_plane *plane, char *pos_str);
void			parse_plane_normal(t_plane *plane, char *normal_str);
int				parse_plane_color(t_plane *plane, char *color_str);
t_plane			*set_plane_properties(void);
void			parse_sphere_position(t_sphere *sphere, char *pos_str);
int				parse_sphere_radius(t_sphere *sphere, char *radius_str);
int				parse_sphere_color(t_sphere *sphere, char *color_str);
void			set_sphere_properties(t_scene *scene, t_sphere new_sphere);
void			parse_light_position(t_light *light, char *pos_str);
int				parse_light_intensity(t_light *light, char *intensity_str);
int				parse_light_color(t_light *light, char *color_str);
t_light			*set_light_properties(void);
int				parse_camera_position(t_camera *camera, char *pos_str);
int				parse_camera_orientation(t_camera *camera, char *orient_str);
int				parse_camera_fov(t_camera *camera, char *fov_str);

void			ft_error(char *message);

void			ft_init_mlx(t_mlx *mlx);

// free
void			free_split(char **split);
void			free_scene(t_scene *scene);
// crispy
void			free_spheres(t_sphere *spheres);
void			free_planes(t_plane *planes);
void			free_cylinders(t_cylinder *cylinders);
void			free_lights(t_light *lights);
int				check_cylinder_hits(t_cylinder cyl, t_pixel px, float *t);
void			update_trace_cylinder(t_trace *tr, t_cylinder *cy,
					t_cyhit info);
int				set_cylinder_quadratic(t_cylinder cyl, t_pixel px,
					t_vector axis, t_cyl_hit *hit);

int				parse_error(char *msg, char *value);

// inits
void			init_vector(t_vector *v);
void			init_color(t_color *c);
void			init_ray(t_ray *r);
void			init_camera(t_camera *cam);
void			init_sphere(t_sphere *sp);
void			init_plane(t_plane *pl);
void			init_cylinder(t_cylinder *cy);
void			init_light(t_light *light);
void			init_ambient(t_ambient *ambient);
void			init_scene(t_scene *scene);
void			init_mlx(t_mlx *mlx);
void			init_data(t_data *data);
void			allocate_objects(t_scene *scene);

// mlx
int				ft_close_window(t_mlx *mlx);
void			update_window(int key, t_mlx *mlx);
int				deal_key(int key, t_mlx *mlx);
void			print_menu(t_mlx *param);

// colors
int				create_rgb(int r, int g, int b);
void			fill_background(t_mlx *mlx, t_scene *scene);
int				color_to_int(t_color color);
void			put_pixel(t_mlx *mlx, int x, int y, int color);

// vectors
t_vector		vector_add(t_vector a, t_vector b);
t_vector		vector_sub(t_vector a, t_vector b);
t_vector		vector_scale(t_vector a, float b);
t_vector		vector_normalize(t_vector a);
float			vector_dot(t_vector a, t_vector b);
t_vector		vector_cross(t_vector a, t_vector b);
float			vector_length(t_vector a);
t_vector		get_ray_direction(t_camera *camera, t_mlx *mlx, float x,
					float y);
void			set_pixel(t_mlx *mlx, t_color color, int x, int y);
int				intersect_sphere(t_vector origin, t_vector direction,
					t_sphere sphere, float *t);
int				intersect_plane(t_vector origin, t_vector direction,
					t_plane plane, float *t);
int				intersect_cylinder(t_vector origin, t_vector direction,
					t_cylinder cylinder, float *t);

// environment
t_color			compute_lighting(t_scene *scene, t_vector point,
					t_vector normal, t_color object_color);

// Core lighting functions
void			initialize_light_calc(t_scene *scene, t_light_calc *calc);
t_vector		get_light_direction(t_vector point, t_vector light_pos);

// Light computation functions
t_color			calculate_ambient_light(t_scene *scene, t_color object_color);
t_color			calculate_diffuse_light(t_light light, t_vector normal,
					t_vector light_dir, t_color object_color);
t_color			calculate_specular_light(t_vector light_dir, t_vector normal,
					t_vector view_dir);
t_color			apply_color_corrections(t_color color);
void			prepare_lighting_vectors(t_vector point, t_vector *view_dir);
void			add_light_contribution(t_scene *scene, t_light light,
					t_lighting_data *data);
t_color			vector_add_color(t_color a, t_color b);

// Shadow functions
int				check_sphere_shadows(t_scene *scene, t_vector point,
					t_vector light_dir, float light_distance);
int				check_plane_shadows(t_scene *scene, t_vector point,
					t_vector light_dir, float light_distance);
int				check_cylinder_shadows(t_scene *scene, t_vector point,
					t_vector light_dir, float light_distance);
int				is_in_shadow(t_scene *scene, t_vector point,
					t_vector light_pos);

// rendering
void			draw_sphere(t_mlx *mlx, t_scene *scene, t_sphere sphere);
void			draw_plane(t_mlx *mlx, t_scene *scene, t_plane plane);
void			draw_scene(t_mlx *mlx, t_scene *scene);

#endif
