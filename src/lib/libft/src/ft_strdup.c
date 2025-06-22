/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <alphbarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:44:42 by alphbarr          #+#    #+#             */
/*   Updated: 2024/01/25 17:37:28 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	l;
	char	*c;

	l = ft_strlen(s) + 1;
	if (s == NULL)
		return (NULL);
	c = (char *)malloc(l);
	if (c == NULL)
		return (NULL);
	ft_strlcpy(c, s, l);
	return (c);
}
/*
int	main()
{
	const char	*o = "Hola";
	char	*c = ft_strdup(o);
	printf("%s", c);
	free(c);
	return (0);
}*/
