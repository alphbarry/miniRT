/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:05:52 by alphbarr          #+#    #+#             */
/*   Updated: 2025/04/24 20:55:17 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minirt.h"

int	parse_color(char *str, t_color *color)
{
	int		i;
	char	**split;

	i = 0;
	split = ft_split(str, ',');
	if (!split || !split[0] || !split[1] || !split[2])
		return (1);
	while (split[i])
	{
		if (i > 2 || !ft_isdigit(split[i][0]))
			return (1);
		i++;
	}
	if (i != 3)
		return (1);
	color->r = ft_atoi(split[0]);
	color->g = ft_atoi(split[1]);
	color->b = ft_atoi(split[2]);
	if (color->r < 0 || color->r > 255 || color->g < 0 || color->g > 255
		|| color->b < 0 || color->b > 255)
		return (free_split(split), 1);
	free_split(split);
	return (0);
}
