/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:42:14 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/08/05 11:09:50 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_fd
{
	int			fdm;
	char		*data;
	struct s_fd	*next;
}	t_fd;

t_fd    *init_storage(int fd);
t_fd    *get_storage(int fd, t_fd *storage);
void	clean_storage(t_fd **head);
size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
int		get_idx(char *str);
char	*shift_previous(char *previous);
char	*get_linee(char *previous);
void	ft_concat(char *dst, char *prefix, char *sufix);
char	*get_buf(char *previous, int *bytswrtn, int fd);
char	*get_next_line(int fd);

#endif
