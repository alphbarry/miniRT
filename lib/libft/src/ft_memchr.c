/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <alphbarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 20:46:39 by alphbarr          #+#    #+#             */
/*   Updated: 2024/01/23 17:25:41 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*d;

	i = 0;
	d = (unsigned char *)s;
	while (i < n)
	{
		if (d[i] == (unsigned char)c)
			return ((void *)&d[i]);
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
	char	a[] = "Hola Mdre";
	int		c;

	c = 'a';
		printf("%p", ft_memchr(a, c, sizeof(a)));
      return (0);
}*/
