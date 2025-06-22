/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <alphbarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:06:18 by alphbarr          #+#    #+#             */
/*   Updated: 2024/01/25 17:12:44 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t o, size_t size)
{
	size_t	t;
	void	*m;

	t = o * size;
	m = malloc(t);
	if (m != NULL)
		ft_memset(m, 0, t);
	return (m);
}
/*
int main()
{
	int	*a;
	int	n = 5;
	a = (int *)ft_calloc(n, sizeof(int));
	if (a == NULL)
	{
		printf("Error");
		return (1);
	}
	free(a);
	return (0);
}*/
