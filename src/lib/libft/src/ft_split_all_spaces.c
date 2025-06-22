/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_all_spaces.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgomez-z <cgomez-z@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 21:50:20 by cgomez-z          #+#    #+#             */
/*   Updated: 2025/06/02 22:07:07 by cgomez-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

int	is_space(int c)
{
	return ((c >= 9 && c <= 13) || c == ' ' || c == '\0');
}

static int	ft_count_words(char const *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (!is_space(s[i]) && is_space(s[i + 1]))
			++count;
		i++;
	}
	return (count);
}

static char	*ft_create_words(char const *s, int *pos)
{
	char	*word;
	int		in;
	int		end;

	in = 0;
	end = 0;
	while (is_space(s[in]) && s[in])
		in++;
	end = in;
	while (!is_space(s[end]) && s[end])
	{
		end++;
	}
	word = ft_substr(s, in, end - in);
	if (word == NULL)
		return (NULL);
	*pos += end;
	return (word);
}

static void	ft_free(char **split, int words)
{
	int	i;

	i = 0;
	while (i != words)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	**ft_split_all_spaces(char const *s)
{
	char	**split;
	int		words;
	int		i;
	int		pos;

	i = 0;
	pos = 0;
	words = ft_count_words(s);
	split = malloc((words + 1) * sizeof(char *));
	if (split == NULL)
		return (NULL);
	while (i < words)
	{
		split[i] = ft_create_words(s + pos, &pos);
		if (split[i] == NULL)
		{
			ft_free(split, i);
			return (NULL);
		}
		i++;
	}
	split[i] = NULL;
	return (split);
}
