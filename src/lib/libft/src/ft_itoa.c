/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <alphbarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 00:52:17 by alphbarr          #+#    #+#             */
/*   Updated: 2024/01/29 19:16:05 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

int	calcular_long(long n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*fill(char *r, long l, long nl)
{
	if (nl == 0)
		r[0] = '0';
	else
	{
		if (nl < 0)
		{
			r[0] = '-';
			nl *= -1;
		}
		while (l > 0 && nl != 0)
		{
			r[--l] = (nl % 10) + '0';
			nl /= 10;
		}
	}
	return (r);
}

char	*ft_itoa(int n)
{
	long	l;
	long	nl;
	char	*r;

	l = calcular_long(n);
	nl = n;
	r = (char *)malloc(sizeof(char) * (l + 1));
	if (!r)
		return (NULL);
	r[l] = '\0';
	return (fill(r, l, nl));
}
/*
int	main()
{
	int	n = 9;
	char	*r = ft_itoa(n);
	printf("Numero original :%d\n", n);
	printf("Numero convertido a cadena: %s\n", r);
	free(r);
	return (0);   
}*/
