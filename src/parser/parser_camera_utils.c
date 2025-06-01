/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_camera_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgomez-z <cgomez-z@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 02:26:01 by cgomez-z          #+#    #+#             */
/*   Updated: 2025/06/01 02:26:13 by cgomez-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	parse_camera_position(t_camera *camera, char *pos_str)
{
	char	**pos;

	pos = ft_split(pos_str, ',');
	if (!validate_coordinates(pos, "Invalid camera position", pos_str))
		return (free_split(pos), 0);
	camera->position.x = ft_atoif(pos[0]);
	camera->position.y = ft_atoif(pos[1]);
	camera->position.z = ft_atoif(pos[2]);
	free_split(pos);
	return (1);
}

int	parse_camera_orientation(t_camera *camera, char *orient_str)
{
	char	**trid;

	trid = ft_split(orient_str, ',');
	if (!validate_coordinates(trid, "Invalid camera orientation", orient_str))
		return (free_split(trid), 0);
	camera->tridimensional.x = ft_atoif(trid[0]);
	camera->tridimensional.y = ft_atoif(trid[1]);
	camera->tridimensional.z = ft_atoif(trid[2]);
	free_split(trid);
	if (!validate_numeric_range(camera->tridimensional.x, -1, 1,
			"Camera orientation x out of range")
		|| !validate_numeric_range(camera->tridimensional.y, -1, 1,
			"Camera orientation y out of range")
		|| !validate_numeric_range(camera->tridimensional.z, -1, 1,
			"Camera orientation z out of range"))
		return (0);
	return (1);
}

int	parse_camera_fov(t_camera *camera, char *fov_str)
{
	if (!fov_str)
	{
		parse_error("Camera FOV missing", NULL);
		return (0);
	}
	camera->fov = ft_atoi(fov_str);
	if (!validate_numeric_range(camera->fov, 0, 180, "Camera FOV out of range"))
		return (0);
	return (1);
}
