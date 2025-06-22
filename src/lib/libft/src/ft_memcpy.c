/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <alphbarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:06:56 by alphbarr          #+#    #+#             */
/*   Updated: 2024/01/26 19:04:42 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned const char	*s;
	unsigned char		*d;

	d = (unsigned char *) dst;
	s = (unsigned char *) src;
	i = 0;
	while (dst == src || !n)
	{
		return (dst);
	}
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}
/*
int	main()
{
	char	*d;
	const char	*s = "Nos fuimos a la playa";
	size_t	n = 10;
	char	*r = ft_memcpy(d, s, n);
	printf("%s", r);
	return (0);
}*/
