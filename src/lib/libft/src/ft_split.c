/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <alphbarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 11:27:51 by alphbarr          #+#    #+#             */
/*   Updated: 2024/02/05 18:09:50 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

char	**my_free_split(char **split)
{
	size_t	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}

int	count_word(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] != c && s[i])
				i++;
		}
		else
			i++;
	}
	return (count);
}

char	**allocate_word(char const *s, char c, char **str, int i)
{
	size_t	j;
	int		start;

	start = -1;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i] != c && s[i] != '\0')
				i++;
			if (start >= 0)
				str[j] = ft_substr(s, start, i - start);
			if (!str[j])
				return (my_free_split(str));
			if (start >= 0)
				j++;
		}
		else
			i++;
	}
	str[j] = NULL;
	return (str);
}

char	**malloc_split(char const *s, char c)
{
	char	**str;

	str = (char **)malloc((count_word(s, c) + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	return (allocate_word(s, c, str, 0));
}

char	**ft_split(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] == c && s[i] != '\0')
		i++;
	return (malloc_split(s + i, c));
}
/*
int main(void)
{
	int		i = 0;
//	int		j = 0;

	char	**a;
	a = ft_split("holla!", ' ');
	while (a[i])
		printf("%s\n", a[i++]);
	i = 0;
	while (a[i])
		free(a[i++]);
	free(a);
	return 0;
}*/
