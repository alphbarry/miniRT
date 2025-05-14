#include "../../inc/minirt.h"

t_vector	get_ray_direction(t_camera *camera, t_mlx *mlx, float x, float y)
{
	t_vector	direction;
	t_vector	basis[3]; // 0 = forward, 1 = right, 2 = up
	float		factor[3]; // factor[0] = aspect, [1] = fov_scale, [2] = dummy px/py reuse

	factor[0] = (float)mlx->win_x / (float)mlx->win_y;// aspect ratio
	factor[1] = tanf(camera->fov * 0.5f * M_PI / 180.0f);// fov scale

	basis[0] = vector_normalize(camera->tridimensional);// forward
	basis[2] = (t_vector){0.0f, 1.0f, 0.0f};// up
	if (fabs(vector_dot(basis[0], basis[2])) > 0.999f)// if forward is aligned with up
		basis[2] = (t_vector){0.0f, 0.0f, 1.0f};// up
	basis[1] = vector_normalize(vector_cross(basis[2], basis[0]));// right
	basis[2] = vector_cross(basis[0], basis[1]);// up

	// px
	factor[2] = (2.0f * ((x + 0.5f) / mlx->win_x) - 1.0f) * factor[0] * factor[1];
	direction = vector_scale(basis[1], factor[2]);
	// py
	factor[2] = (1.0f - 2.0f * ((y + 0.5f) / mlx->win_y)) * factor[1];
	direction = vector_add(direction, vector_scale(basis[2], factor[2]));
	direction = vector_add(direction, basis[0]);

	return (vector_normalize(direction));
}

void	set_pixel(t_mlx *mlx, t_color color, int x, int y)
{
	int	i;

	i = ((y * mlx->size_line) + (x * mlx->bpp / 8));
	mlx->img_data[i] = color.b;
	mlx->img_data[i + 1] = color.g;
	mlx->img_data[i + 2] = color.r;
}

void	draw_scene(t_mlx *mlx, t_scene *scene)
{
	int	i;

	fill_background(mlx, scene);
	i = 0;
	while (i < scene->sphere_count)
	{
		draw_sphere(mlx, scene->spheres[i], scene->camera);
		i++;
	}
	i = 0;
	while (i < scene->plane_count)
	{
		draw_plane(mlx, scene->planes[i], scene->camera);
		i++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
}
