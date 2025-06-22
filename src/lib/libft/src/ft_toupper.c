/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <alphbarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:18:53 by alphbarr          #+#    #+#             */
/*   Updated: 2024/01/09 17:30:40 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "stdio.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
	{
		c -= 32;
	}
	return (c);
}
/*
int	main()
{
	char	a = 'a';
	int	b = ft_toupper(a);
	printf("%d", b);
	return (0);
}*/
