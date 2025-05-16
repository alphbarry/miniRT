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
    int         x, y, i;
    float       t, closest_t;
    t_vector    ray_direction, origin;
    t_color     color;
    t_vector    hit_point, normal;
/*
    fprintf(stderr, "\nDEBUG: Scene Configuration:\n");
    fprintf(stderr, "Camera: position(%.1f,%.1f,%.1f) direction(%.1f,%.1f,%.1f)\n",
        scene->camera.position.x, scene->camera.position.y, scene->camera.position.z,
        scene->camera.tridimensional.x, scene->camera.tridimensional.y, scene->camera.tridimensional.z);
    
    i = 0;
    while (i < scene->sphere_count)
    {
        fprintf(stderr, "Sphere %d: center(%.1f,%.1f,%.1f) radius(%.1f)\n",
            i, scene->spheres[i].center.x, scene->spheres[i].center.y, 
            scene->spheres[i].center.z, scene->spheres[i].radius);
        i++;
    }
    
    i = 0;
    while (i < scene->plane_count)
    {
        fprintf(stderr, "Plane %d: point(%.1f,%.1f,%.1f) normal(%.1f,%.1f,%.1f)\n",
            i, scene->planes[i].point.x, scene->planes[i].point.y, scene->planes[i].point.z,
            scene->planes[i].normal.x, scene->planes[i].normal.y, scene->planes[i].normal.z);
        i++;
    }
    fprintf(stderr, "\n");*/

    fill_background(mlx, scene);
    origin = scene->camera.position;
    
    //fprintf(stderr, "DEBUG: Starting unified raytracing with %d spheres and %d planes\n", 
        //scene->sphere_count, scene->plane_count);

    y = 0;
    while (y < mlx->win_y)
    {
        x = 0;
        while (x < mlx->win_x)
        {
            closest_t = INFINITY;
            ray_direction = get_ray_direction(&scene->camera, mlx, x, y);
            
            // Check spheres
            i = 0;
            while (i < scene->sphere_count)
            {
                if (intersect_sphere(origin, ray_direction, scene->spheres[i], &t))
                {
                    if (t < closest_t)
                    {
                        closest_t = t;
                        hit_point = vector_add(origin, vector_scale(ray_direction, t));
                        normal = vector_normalize(vector_sub(hit_point, scene->spheres[i].center));
                        color = compute_lighting(scene, hit_point, normal, scene->spheres[i].color);
                    }
                }
                i++;
            }
            
            // Check planes
            i = 0;
            while (i < scene->plane_count)
            {
                if (intersect_plane(origin, ray_direction, scene->planes[i], &t))
                {
                    if (t < closest_t)
                    {
                        closest_t = t;
                        hit_point = vector_add(origin, vector_scale(ray_direction, t));
                        normal = vector_normalize(scene->planes[i].normal);
                        color = compute_lighting(scene, hit_point, normal, scene->planes[i].color);
                    }
                }
                i++;
            }

			// Check cylinders
			// Check cylinders
			i = 0;
		while (i < scene->cylinder_count)
		{
			if (intersect_cylinder(origin, ray_direction, scene->cylinders[i], &t))
			{
				if (t < closest_t)
				{
					closest_t = t;
					hit_point = vector_add(origin, vector_scale(ray_direction, t));
	
					// Cálculo de la normal
					t_vector axis = vector_normalize(scene->cylinders[i].normal);
					t_vector to_hit = vector_sub(hit_point, scene->cylinders[i].center);
					float proj = vector_dot(to_hit, axis);
					t_vector closest_axis_point = vector_add(scene->cylinders[i].center, vector_scale(axis, proj));
					normal = vector_normalize(vector_sub(hit_point, closest_axis_point));
					color = compute_lighting(scene, hit_point, normal, scene->cylinders[i].color);
				}
			}
			i++;
}

            
            // Draw the closest intersection
            if (closest_t < INFINITY)
                set_pixel(mlx, color, x, y);
                
            x++;
        }
        y++;
    }
    
    mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
}
