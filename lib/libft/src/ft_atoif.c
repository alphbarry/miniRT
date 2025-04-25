/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoif.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 19:11:56 by alphbarr          #+#    #+#             */
/*   Updated: 2025/04/25 20:26:57 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "libft.h"
#include "../../../inc/minirt.h"

float	ft_atoif(char *str)
{
	size_t	i;
	int		sign;
	float	result;
	float	decimal_factor;

	if (!str || !*str)
		parse_error("NULL STRING", str);
	i = 0;
	sign = 1;
	result = 0;
	decimal_factor = 0.1f;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\t' || str[i] == '\v')
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	if (str[i] < '0' || str[i] > '9')
		parse_error("Invalid number", str);
	while (str[i] >= '0' && str[i] <= '9')
		result = (result * 10) + (str[i++] - '0');
	if (str[i] == '.')
	{
		i++;
		if (str[i] < '0' || str[i] > '9')
			parse_error("Number waited after point", str);
		while (str[i] >= '0' && str[i] <= '9')
		{
			result += (str[i++] - '0') * decimal_factor;
			decimal_factor *= 0.1f;
		}
	}
	if (str[i] != '\0' && str[i] != ' ' && str[i] != '\n')
		parse_error("Invalid caracter after number", str);
	return (result * sign);
}
