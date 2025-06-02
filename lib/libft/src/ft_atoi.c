/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <alphbarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:24:37 by alphbarr          #+#    #+#             */
/*   Updated: 2025/06/02 20:07:59 by cgomez-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../../inc/minirt.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

static void	deletespace(char *str, int i)
{
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\t' || str[i] == '\v')
		i++;
}

int	ft_atoi(char *str)
{
	size_t	i;
	int		sign;
	int		result;

	if (!str || !*str)
		parse_error("NULL STRING", str);
	i = 0;
	sign = 1;
	result = 0;
	deletespace(str, i);
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
	if (str[i] != '\0' && str[i] != ' ' && str[i] != '\n')
		parse_error("Invalid caracter after number", str);
	return (result * sign);
}
