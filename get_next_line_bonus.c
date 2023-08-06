/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:42:14 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/08/06 17:22:55 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	clean_storage(t_fd **head)
{
	t_fd	*tmp[2];

	if (!(*head)-> data)
	{
		tmp[1] = *head;
		*head = (*head)-> next;
		free(tmp[1]);
		return ;
	}
	tmp[0] = *head;
	tmp[1] = (*head)-> next;
	while (tmp[1])
	{
		if (!tmp[1]-> data)
		{
			tmp[0]-> next = tmp[1]-> next;
			free(tmp[1]);
			tmp[1] = tmp[0]-> next;
		}
		else
		{
			tmp[0] = tmp[1];
			tmp[1] = tmp[1]-> next;
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
			return (storage);
		else
		{
			previous = storage;
			storage = storage -> next;
		}
	}
	previous -> next = init_storage(fd);
	return (previous -> next);
}

char	*get_buf(char *previous, int *wrtn, int fd)
{
	char	*buf;
	char	*res;

	if (!previous)
	{
		previous = malloc(1);
		previous[0] = 0;
	}
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	*wrtn = read(fd, buf, BUFFER_SIZE);
	if (*wrtn < 0)
	{
		res = malloc(1);
		*res = 0;
	}
	else
	{
		buf[*wrtn] = 0;
		res = malloc(sizeof(char) * (ft_strlcpy(previous, "", 0) + *wrtn + 1));
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
