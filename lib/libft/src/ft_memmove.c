/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <alphbarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:46:01 by alphbarr          #+#    #+#             */
/*   Updated: 2024/01/26 18:58:09 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	unsigned const char	*s;
	unsigned char		*d;

	d = (unsigned char *)dst;
	s = (unsigned const char *)src;
	i = 0;
	if (!len || dst == src)
		return (dst);
	if (src < dst)
	{
		while (len--)
			d[len] = s[len];
	}
	else
	{
		while (i < len)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dst);
}
/*
int	main()
{
	char	*a = "lorem ipum dolor sit a";
	char	b[20];
	ft_memmove(b, a, 8);
	printf("%s", b);
	return (0);
}*/
