/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <alphbarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:43:17 by alphbarr          #+#    #+#             */
/*   Updated: 2024/01/25 17:41:33 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "libft.h"

char	*ft_strnstr(const char *h, const char *n, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	ln;

	i = 0;
	ln = ft_strlen(n);
	if (ln == 0)
		return ((char *)&h[i]);
	while (h[i] != '\0' && i < len)
	{
		if (h[i] == n[0])
		{
			j = 0;
			while (h[i + j] == n[j] && j < ln && i + j < len)
			{
				j++;
			}
			if (j == ln)
				return ((char *)&h[i]);
		}
		i++;
	}
	return (NULL);
}
/*
int	main()
{
	const char	*h = "Hello World!";
	const char	*n = "World";
	char	*r = ft_strnstr(h, n, 15);
	printf("%s", r);
	return (0);
}*/
