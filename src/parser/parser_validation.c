/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 22:30:00 by alphbarr          #+#    #+#             */
/*   Updated: 2025/05/16 22:30:00 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	validate_coordinates(char **coords, char *err_msg, char *value)
{
	if (!coords || !coords[0] || !coords[1] || !coords[2])
	{
		parse_error(err_msg, value);
		return (0);
	}
	return (1);
}

int	validate_numeric_range(float value, float min, float max, char *err_msg)
{
	if (value < min || value > max)
	{
		parse_error(err_msg, NULL);
		return (0);
	}
	return (1);
}

int	validate_color_component(int value, char *component, char *err_msg)
{
	if (value < 0 || value > 255)
	{
		parse_error(err_msg, component);
		return (0);
	}
	return (1);
}

int	validate_color_values(char **rgb, char *err_msg, char *value)
{
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
	{
		parse_error(err_msg, value);
		return (0);
	}
	return (1);
}

int	validate_split(char **split, char *err_msg, char *line)
{
	if (!split)
	{
		parse_error(err_msg, line);
		return (0);
	}
	return (1);
}

