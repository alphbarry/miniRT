/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <alphbarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:56:18 by alphbarr          #+#    #+#             */
/*   Updated: 2024/07/02 13:24:57 by alphbarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* Comprueba si hay un \n en la lista actual. */

int	found_newline(t_list *stash)
{
	int		i;
	t_list	*current;

	if (stash == NULL)
		return (0);
	current = ft_lst_get_last(stash);
	i = 0;
	while (current->content[i])
	{
		if (current->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

/* Devuelve n puntero al ultimo nodo de nuestro stash */

t_list	*ft_lst_get_last(t_list *stash)
{
	t_list	*current;

	current = stash;
	while (current && current->next)
		current = current->next;
	return (current);
}

/* Calcular el numero de chars en la linea actual incluyendo el \n */

void	generate_line(char **line, t_list *stash)
{
	int	i;
	int	len;

	len = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		stash = stash->next;
	}
	*line = malloc(sizeof(char) * (len + 1));
}

/* Free de stash. */

void	free_stash(t_list **stash, char *buf, t_list *node)
{
	t_list	*current;
	t_list	*next;

	if (stash && *stash)
	{
		current = *stash;
		while (current)
		{
			next = current->next;
			free(current->content);
			free(current);
			current = next;
		}
		*stash = NULL;
	}
	if (buf != NULL)
		free(buf);
	if (node != NULL)
	{
		free(node->content);
		free(node);
		node = NULL;
	}
}
/*
int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (*(str++))
		len++;
	return (len);
}*/
