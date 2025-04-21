/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <alphbarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:22:30 by alphbarr          #+#    #+#             */
/*   Updated: 2024/01/09 18:15:32 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "stdio.h"
#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*d;

	d = s;
	i = 0;
	while (i < n)
	{
		d[i] = 0;
		i++;
	}
}
/*
int	main()
{
	char	a[20];
	ft_bzero(a, 15);
	printf("%s\n", a);
	return (0);
}*/
