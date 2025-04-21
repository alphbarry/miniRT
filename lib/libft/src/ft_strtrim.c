/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <alphbarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:32:27 by alphbarr          #+#    #+#             */
/*   Updated: 2024/02/02 18:18:38 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

static int	ft_isin(const char	*s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		i++;
	}
	if (s[i] == c)
		return (1);
	else
		return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*r;

	i = 0;
	j = ft_strlen(s1);
	while (s1[i] && ft_isin(set, s1[i]))
		i++;
	while (j > i && ft_isin(set, s1[j - 1]))
		j--;
	r = (char *)malloc(sizeof(*s1) * (j - i + 1));
	if (!r)
		return (NULL);
	k = 0;
	while (i < j)
	{
		r[k++] = s1[i++];
	}
	r[k] = '\0';
	return (r);
}
/*
int	main(void)
{
	const char	*a ="";
	const char	b[] = "";
	char	*r;

	r = ft_strtrim(a, b);
	printf("%s\n", a);
	printf("%s\n", r);
	free(r);
	return (0);
}*/
