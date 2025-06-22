/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <alphbarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:24:37 by alphbarr          #+#    #+#             */
/*   Updated: 2024/01/10 17:13:23 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "stdio.h"
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	ld;
	size_t	ls;

	ld = ft_strlen(dst);
	ls = ft_strlen(src);
	i = ld;
	j = 0;
	if (dstsize < 1)
		return (ls + dstsize);
	while (src[j] != '\0' && i < dstsize - 1)
	{
		dst[i] = src[j];
		j++;
		i++;
	}
	dst[i] = '\0';
	if (dstsize < ld)
		return (ls + dstsize);
	else
		return (ls + ld);
}
/*
int main()
{
	char	d[10] = "Mundo";
	char	s[] = "Hola";
	ft_strlcat(d, s, sizeof(d));
	printf("%s", d);
	return (0);
}*/
