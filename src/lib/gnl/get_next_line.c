/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <alphbarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:55:41 by alphbarr          #+#    #+#             */
/*   Updated: 2025/06/02 00:06:40 by cgomez-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_g_list	*stash = NULL;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	read_and_stash(fd, &stash);
	if (stash == NULL)
		return (NULL);
	extract_line(stash, &line);
	if (line == NULL)
	{
		free_stash(&stash, NULL, NULL);
		stash = NULL;
		return (NULL);
	}
	clean_stash(&stash, 0);
	if (line[0] == '\0')
	{
		free_stash(&stash, NULL, NULL);
		stash = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

/* Usar read() para anadir caracteres a stash */

int	read_and_stash(int fd, t_g_list **stash)
{
	char	*buf;
	int		readed;

	readed = 1;
	while (!found_newline(*stash) && readed != 0)
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buf == NULL)
			return (free_stash(stash, buf, NULL), 0);
		readed = (int)read(fd, buf, BUFFER_SIZE);
		if (readed == -1)
			return (free_stash(stash, buf, NULL), 0);
		if (*stash == NULL && readed == 0)
		{
			free(buf);
			return (0);
		}
		buf[readed] = '\0';
		add_to_stash(stash, buf, readed);
		if (*stash == NULL || stash == NULL)
			return (0);
		free(buf);
	}
	return (1);
}

/* Anadir el contenido de nuestro buffer al final de stash */

int	add_to_stash(t_g_list **stash, char *buf, int readed)
{
	int			i;
	t_g_list	*last;
	t_g_list	*new_node;

	new_node = malloc(sizeof(t_g_list));
	if (new_node == NULL)
		return (free_stash(stash, buf, NULL), 0);
	new_node->next = NULL;
	new_node->content = malloc(sizeof(char) * (readed + 1));
	if (new_node->content == NULL)
		return (free_stash(stash, buf, new_node), 0);
	i = -1;
	while (buf[++i] && i < readed)
		new_node->content[i] = buf[i];
	new_node->content[i] = '\0';
	if (*stash == NULL)
	{
		*stash = new_node;
		return (0);
	}
	last = ft_lst_get_last(*stash);
	last->next = new_node;
	return (1);
}

/* Extraer todos los caracteres de stash y guardarlos en line.
 * parando cuando se encuentre un \n */

void	extract_line(t_g_list *stash, char **line)
{
	int	i;
	int	j;

	if (stash == NULL)
		return ;
	generate_line(line, stash);
	if (*line == NULL)
		return ;
	j = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				(*line)[j++] = stash->content[i];
				break ;
			}
			(*line)[j++] = stash->content[i++];
		}
		stash = stash->next;
	}
	(*line)[j] = '\0';
}

int	clean_stash(t_g_list **stash, int j)
{
	t_g_list	*last;
	t_g_list	*clean_node;
	int			i;

	clean_node = malloc(sizeof(t_g_list));
	if (stash == NULL || clean_node == NULL)
		return (free_stash(stash, NULL, clean_node), 0);
	clean_node->next = NULL;
	last = ft_lst_get_last(*stash);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content && last->content[i] == '\n')
		i++;
	clean_node->content = malloc(sizeof(char) * ((ft_strlen(last->content) - i)
				+ 1));
	if (clean_node->content == NULL)
		return (free_stash(stash, NULL, clean_node), 0);
	j = 0;
	while (last->content[i])
		clean_node->content[j++] = last->content[i++];
	clean_node->content[j] = '\0';
	free_stash(stash, NULL, NULL);
	*stash = clean_node;
	return (1);
}
/*
int	main(int argc, char **argv)
{
	int		fd;
	char	*line;

	fd = open("text/1char.txt", O_RDONLY, 0777);
	line = get_next_line(fd);
	while (!line)
	{
		printf("%s\n", line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (0);
}*/
