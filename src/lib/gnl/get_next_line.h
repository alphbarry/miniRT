/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphbarr <alphbarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 20:07:47 by alphbarr          #+#    #+#             */
/*   Updated: 2025/04/21 21:54:46 by alpha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct s_g_list
{
	char			*content;
	struct s_g_list	*next;
}					t_g_list;

char				*get_next_line(int fd);
int					found_newline(t_g_list *stash);
t_g_list			*ft_lst_get_last(t_g_list *stash);
int					read_and_stash(int fd, t_g_list **stash);
int					add_to_stash(t_g_list **stash, char *buf, int readed);
void				extract_line(t_g_list *stash, char **line);
void				generate_line(char **line, t_g_list *stash);
int					clean_stash(t_g_list **stash, int j);
int					ft_strlen(const char *str);
void				free_stash(t_g_list **stash, char *buf, t_g_list *node);

#endif
