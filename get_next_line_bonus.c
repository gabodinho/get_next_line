/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:42:14 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/08/05 11:49:57 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	clean_storage(t_fd **head)
{
	t_fd	*temp;
	t_fd	*prev;

	if (!(*head) -> data)
	{
		temp = *head;
		*head = (*head) -> next;
		free(temp);
		return ;
	}
	prev = *head;
	temp = (*head) -> next;
	while (temp)
	{
	        if (!temp -> data)
	        {
		                prev -> next = temp -> next;
		                free(temp);
		                temp = prev -> next;
	        }
	        else
			{
				prev = temp;
				temp = temp -> next;
			}
	}
}

t_fd	*init_storage(int fd)
{
	t_fd	*new;

	new = malloc(sizeof(t_fd));
	new -> fdm = fd;
	new -> data = 0;
	new -> next = 0;
	return (new);
}

t_fd	*get_storage(int fd, t_fd *storage)
{
	t_fd	*previous;

	while (storage)
	{
		if (storage -> fdm == fd)
			return(storage);
		else
		{
			previous = storage;
			storage = storage -> next;
		}
	}
	previous -> next = init_storage(fd);
	return (previous -> next);
}

void	ft_concat(char *dst, char *prefix, char *sufix)
{
	while (*prefix)
		*dst++ = *prefix++;
	while (*sufix)
		*dst++ = *sufix++;
	*dst = 0;
}

char	*get_buf(char *previous, int *bytswrtn, int fd)
{
	char	*buf;
	char	*res;

	if (!previous)
	{
		previous = malloc(1);
		previous[0] = 0;
	}
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	*bytswrtn = read(fd, buf, BUFFER_SIZE);
	if (*bytswrtn < 0)
	{
		res = malloc(1);
		*res = 0;
	}
	else
	{
		buf[*bytswrtn] = 0;
		res = malloc(sizeof(char) * (ft_strlen(previous) + *bytswrtn + 1));
		ft_concat(res, previous, buf);
	}
	free(buf);
	free(previous);
	return (res);
}

char	*get_next_line(int fd)
{
	static t_fd	*storage;
	t_fd		*current;
	char		*previous;
	char		*line;
	int			res;

	if (fd < 0)
		return (0);
	if (!storage)
		storage = init_storage(fd);
	current = get_storage(fd, storage);
	previous = current -> data;
	res = BUFFER_SIZE;
	while (res == BUFFER_SIZE)
	{
		if (get_idx(previous))
			break ;
		previous = get_buf(previous, &res, fd);
	}
	line = get_linee(previous);
	current -> data = shift_previous(previous);
	clean_storage(&storage);
	return (line);
}
