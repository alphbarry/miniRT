/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 13:17:56 by alphbarr          #+#    #+#             */
/*   Updated: 2024/12/05 19:48:16 by alpha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*int	ft_strcmp(const char *s1, const char *s2)
>>>>>>> alpha
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[2] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}*/
int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	int		cmp1;
	int		cmp2;
	char	*s1;
	char	*s2;

	s1 = strdup("echo hola que tal");
	s2 = strdup("echo ");
	cmp1 = strcmp(s1, s2);
	cmp2 = ft_strcmp(s1, s2);
	printf("Original:%i\n", cmp1);
	printf("Mine:%i\n", cmp2);
	return (0);
}*/
