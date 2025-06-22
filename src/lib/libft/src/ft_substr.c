/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <alphbarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:09:43 by alphbarr          #+#    #+#             */
/*   Updated: 2024/02/05 17:36:39 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

static size_t	len_subs(char const *s, unsigned int start, size_t len)
{
	size_t	l;

	l = ft_strlen(s);
	if (start >= l)
		return (0);
	if (len > l - start)
		len = l - start;
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	l;
	char	*c;

	i = 0;
	if (!s)
		return (NULL);
	l = len_subs(s, start, len);
	if (len == 0)
		return (ft_strdup(""));
	c = (char *)malloc(sizeof(*s) * (l + 1));
	if (!c)
		return (NULL);
	while (i < l)
	{
		c[i] = s[start];
		i++;
		start++;
	}
	c[i] = '\0';
	return (c);
}
/*
int	main()
{
	const char	*o = "Hola!";
	char	*r = ft_substr(o, 6, 6);
	printf("%s", r);
	free(r);
	return (0);
}*/
