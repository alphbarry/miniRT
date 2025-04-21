/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgomez-z <cgomez-z@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 18:46:22 by cgomez-z          #+#    #+#             */
/*   Updated: 2025/04/13 22:09:24 by alpha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*aux;

	aux = *lst;
	while (aux)
	{
		tmp = aux->next;
		del(aux->content);
		free(aux);
		aux = tmp;
	}
	*lst = NULL;
}
