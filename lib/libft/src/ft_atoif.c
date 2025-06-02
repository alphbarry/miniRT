/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoif.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 19:11:56 by alphbarr          #+#    #+#             */
/*   Updated: 2025/06/02 20:34:51 by cgomez-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../../inc/minirt.h"
#include "libft.h"
#include <stdio.h>

int	ifelseif(char *str, int i)
{
	if (!str || !*str)
		parse_error("NULL STRING", str);
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\t' || str[i] == '\v')
		i++;
	return (i);
}

float	parse_decimal_part(char *str, size_t *i)
{
	float	dec;
	float	factor;

	dec = 0.0f;
	factor = 0.1f;
	if (str[*i] == '.')
	{
		(*i)++;
		if (str[*i] < '0' || str[*i] > '9')
			parse_error("Number waited after point", str);
		while (str[*i] >= '0' && str[*i] <= '9')
		{
			dec += (str[*i] - '0') * factor;
			factor *= 0.1f;
			(*i)++;
		}
	}
	return (dec);
}

float	ft_atoif(char *str)
{
	size_t	i;
	int		sign;
	float	res;
	float	dec;

	i = 0;
	i = ifelseif(str, i);
	sign = 1;
	if (str[i] == '+')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	if (str[i] < '0' || str[i] > '9')
		parse_error("Invalid number", str);
	res = 0.0f;
	while (str[i] >= '0' && str[i] <= '9')
		res = (res * 10.0f) + (str[i++] - '0');
	dec = parse_decimal_part(str, &i);
	if (str[i] != '\0' && str[i] != ' ' && str[i] != '\n')
		parse_error("Invalid caracter after number", str);
	return ((res + dec) * sign);
}
