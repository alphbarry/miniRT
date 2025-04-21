/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <alphbarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:52:00 by alphbarr          #+#    #+#             */
/*   Updated: 2024/01/25 17:38:35 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	size_t	ld;
	size_t	ls;
	size_t	lt;

	ld = ft_strlen(s1);
	ls = ft_strlen(s2);
	lt = ld + ls;
	s3 = (char *)malloc(lt + 1);
	if (s3 == NULL)
		return (NULL);
	ft_strlcpy(s3, s1, ld + 1);
	ft_strlcat(s3, s2, lt + 1);
	return (s3);
}
/*
int	main()
{
	const char	*s1 = "Hola";
	const char	*s2 = ", Mundo!";
	char	*c = ft_strjoin(s1, s2);
	printf("%s\n", c);
	free(c);
	return (0);
}*/
