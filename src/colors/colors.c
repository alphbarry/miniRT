/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:05:52 by alphbarr          #+#    #+#             */
/*   Updated: 2025/05/16 23:27:36 by alpha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minirt.h"

int	color_to_int(t_color color)
{
	return ((color.r & 0xFF) << 16 | (color.g & 0xFF) << 8 | (color.b & 0xFF));
}

t_color	vector_add_color(t_color a, t_color b)
{
	t_color	result;

	result.r = fmin(a.r + b.r, 255.0f);
	result.g = fmin(a.g + b.g, 255.0f);
	result.b = fmin(a.b + b.b, 255.0f);
	return (result);
}

void	put_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= mlx->win_x || y < 0 || y >= mlx->win_y)
		return ;
	dst = mlx->img_data + (y * mlx->size_line + x * (mlx->bpp / 8));
	*(unsigned int *)dst = color;
}

int	apply_ratio_to_color(t_color color, float ratio)
{
	int	r;
	int	g;
	int	b;

	r = (int)(color.r * ratio);
	g = (int)(color.g * ratio);
	b = (int)(color.b * ratio);

	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return (r << 16 | g << 8 | b);
}

void fill_background(t_mlx *mlx, t_scene *scene)
{
	int x;
	int y;
	int color;

	// Aplica el ratio de la luz ambiente al color
	color = apply_ratio_to_color(scene->ambient.color, scene->ambient.ratio);
	y = 0;
	while (y < mlx->win_y)
	{
		x = 0;
		while (x < mlx->win_x)
		{
			put_pixel(mlx, x, y, color);
			x++;
		}
		y++;
	}
	// Muestra la imagen generada en la ventana
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
}
