/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <alphbarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 19:47:09 by alphbarr          #+#    #+#             */
/*   Updated: 2024/02/02 20:08:18 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	f;

	f = 0;
	i = ft_strlen(s);
	while (i >= 0 && f == 0)
	{
		if (s[i] == (char)c)
		{
			return ((char *)&s[i]);
			f = 1;
		}
		i--;
	}
	return (NULL);
}
/*
int	main(void)
{
	char	*a;
	int		c;

	a = "Mundomanana";
	c = 'n';
	printf("%s", ftstrrchr(a, c));
	return (0);
}*/
