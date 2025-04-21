/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <alphbarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:13:43 by alphbarr          #+#    #+#             */
/*   Updated: 2024/01/25 17:16:42 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*d;
	const unsigned char	*s;

	i = 0;
	d = (const unsigned char *)s1;
	s = (const unsigned char *)s2;
	while (n -- > 0)
	{
		if (d[i] == s[i])
			i++;
		else
			return (d[i] - s[i]);
	}
	return (0);
}
/*
int	main ()
{
	char	a[] = "Hello";
	char	b[] = "Hola";
	int r = ft_memcmp(a, b, 4);
	printf("%d", r);
	return (0);
}*/
