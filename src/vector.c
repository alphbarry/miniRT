/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpha <alpha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:37:41 by alpha             #+#    #+#             */
/*   Updated: 2025/04/21 19:37:41 by alpha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

/*
** Create a new 3D vector
*/

t_vec3	ft_vec3_create(double x, double y, double z)
{
	t_vec3	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

/*
** Add two vectors
*/

t_vec3	ft_vec3_add(t_vec3 v1, t_vec3 v2)
{
	t_vec3	result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return (result);
}

/*
** Subtract two vectors
*/

t_vec3	ft_vec3_sub(t_vec3 v1, t_vec3 v2)
{
	t_vec3	result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return (result);
}

/*
** Multiply a vector by a scalar
*/

t_vec3	ft_vec3_mult(t_vec3 v, double t)
{
	t_vec3	result;

	result.x = v.x * t;
	result.y = v.y * t;
	result.z = v.z * t;
	return (result);
}

/*
** Divide a vector by a scalar
*/

t_vec3	ft_vec3_div(t_vec3 v, double t)
{
	t_vec3	result;
	double	inv_t;

	inv_t = 1.0 / t;
	result.x = v.x * inv_t;
	result.y = v.y * inv_t;
	result.z = v.z * inv_t;
	return (result);
}

/*
** Calculate the dot product of two vectors
*/

double	ft_vec3_dot(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

/*
** Calculate the cross product of two vectors
*/

t_vec3	ft_vec3_cross(t_vec3 v1, t_vec3 v2)
{
	t_vec3	result;

	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;
	return (result);
}

/*
** Calculate the length of a vector
*/

double	ft_vec3_length(t_vec3 v)
{
	return (sqrt(ft_vec3_dot(v, v)));
}

/*
** Normalize a vector (make it a unit vector)
*/

t_vec3	ft_vec3_normalize(t_vec3 v)
{
	double	length;
	t_vec3	result;

	length = ft_vec3_length(v);
	if (length < EPSILON)
		return (ft_vec3_create(0, 0, 0));
	result = ft_vec3_div(v, length);
	return (result);
}

/*
** Multiply two color vectors (component-wise)
*/

t_vec3	ft_vec3_color_mult(t_vec3 c1, t_vec3 c2)
{
	t_vec3	result;

	result.x = c1.x * c2.x;
	result.y = c1.y * c2.y;
	result.z = c1.z * c2.z;
	return (result);
}

/*
** Get the reflected vector
*/

t_vec3	ft_vec3_reflect(t_vec3 v, t_vec3 n)
{
	t_vec3	result;
	double	dot_product;

	dot_product = ft_vec3_dot(v, n);
	result = ft_vec3_sub(v, ft_vec3_mult(n, 2.0 * dot_product));
	return (result);
}

/*
** Clamp a vector's components between min and max values
*/

t_vec3	ft_vec3_clamp(t_vec3 v, double min, double max)
{
	t_vec3	result;

	result.x = fmin(fmax(v.x, min), max);
	result.y = fmin(fmax(v.y, min), max);
	result.z = fmin(fmax(v.z, min), max);
	return (result);
}

