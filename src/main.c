/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpha <alpha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:37:41 by alpha             #+#    #+#             */
/*   Updated: 2025/04/21 20:16:31 by alpha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

/*
** Close program and free all allocated resources
*/

int	ft_close_program(t_program *program)
{
	if (program->mlx.img_ptr)
		mlx_destroy_image(program->mlx.mlx_ptr, program->mlx.img_ptr);
	if (program->mlx.win_ptr)
		mlx_destroy_window(program->mlx.mlx_ptr, program->mlx.win_ptr);
	if (program->mlx.mlx_ptr)
	{
		mlx_destroy_display(program->mlx.mlx_ptr);
		free(program->mlx.mlx_ptr);
	}
	exit(0);
	return (0);
}

/*
** Key handler for ESC key to exit program
*/

int	ft_key_handler(int keycode, t_program *program)
{
	if (keycode == 65307)  // ESC key
		ft_close_program(program);
	return (0);
}

/*
** Put a pixel in the image
*/

void	ft_put_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

/*
** Convert RGB color to integer
*/

int	ft_rgb_to_int(t_vec3 color)
{
	int	r;
	int	g;
	int	b;

	r = (int)(fmin(1.0, color.x) * 255);
	g = (int)(fmin(1.0, color.y) * 255);
	b = (int)(fmin(1.0, color.z) * 255);
	return (r << 16 | g << 8 | b);
}

/*
** Initialize MLX, window and image
*/

int	ft_init_mlx(t_program *program)
{
	program->mlx.mlx_ptr = mlx_init();
	if (!program->mlx.mlx_ptr)
		return (ft_error("Failed to initialize MLX"));
	program->mlx.win_ptr = mlx_new_window(program->mlx.mlx_ptr, 
			WIDTH, HEIGHT, "miniRT");
	if (!program->mlx.win_ptr)
	{
		free(program->mlx.mlx_ptr);
		return (ft_error("Failed to create window"));
	}
	program->mlx.img_ptr = mlx_new_image(program->mlx.mlx_ptr, WIDTH, HEIGHT);
	if (!program->mlx.img_ptr)
		return (ft_error("Failed to create image"));
	program->mlx.addr = mlx_get_data_addr(program->mlx.img_ptr, 
			&program->mlx.bits_per_pixel, 
			&program->mlx.line_length, &program->mlx.endian);
	return (0);
}

/*
** Set up event hooks
*/

void	ft_setup_hooks(t_program *program)
{
	mlx_hook(program->mlx.win_ptr, 17, 0, ft_close_program, program);
	mlx_hook(program->mlx.win_ptr, 2, 1L << 0, ft_key_handler, program);
	mlx_loop_hook(program->mlx.mlx_ptr, (int (*)(void *))ft_render_scene, 
			program);
}

/*
** Calculate ray from camera to pixel
*/

t_ray	ft_calculate_ray(t_camera camera, int x, int y)
{
	t_ray	ray;
	double	u;
	double	v;
	t_vec3	direction;

	u = (double)x / (WIDTH - 1);
	v = (double)(HEIGHT - 1 - y) / (HEIGHT - 1);
	direction = ft_vec3_create(
			u - 0.5,
			v - 0.5,
			-1.0 / (2.0 * tan(camera.fov * M_PI / 360.0))
			);
	direction = ft_vec3_normalize(direction);
	ray.origin = camera.position;
	ray.dir = direction;
	return (ray);
}

/*
** Render the scene
*/

int	ft_render_scene(t_program *program)
{
	int		x;
	int		y;
	t_ray	ray;
	t_vec3	color;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray = ft_calculate_ray(program->scene.camera, x, y);
			color = ft_ray_color(ray, program->scene);
			ft_put_pixel(&program->mlx, x, y, ft_rgb_to_int(color));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(program->mlx.mlx_ptr, program->mlx.win_ptr, 
			program->mlx.img_ptr, 0, 0);
	return (0);
}

/*
** Basic error handler
*/

int	ft_error(char *message)
{
	printf("Error: %s\n", message);
	return (1);
}

/*
** Main function
*/

int	main(int argc, char **argv)
{
	t_program	program;

	if (argc != 2)
		return (ft_error("Usage: ./miniRT scene_file.rt"));
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 3, ".rt", 3) != 0)
		return (ft_error("Scene file must have .rt extension"));
	if (ft_init_mlx(&program) != 0)
		return (1);
	if (ft_parse_scene(argv[1], &program.scene) != 0)
	{
		ft_close_program(&program);
		return (1);
	}
	ft_setup_hooks(&program);
	mlx_loop(program.mlx.mlx_ptr);
	return (0);
}

