/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:42:14 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/08/04 12:37:00 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"


// diese funktion in den clean up prozess integrieren
void	clean_storage(t_fd *storage)
{
	t_fd	*current;

	while (storage)
	{
		if (!storage -> data)
		{
			current = storage -> next;
			free(storage);
			storage = current;
		}
	}
}

//dies funktion umschreiben, sodass sie einen pointer returned
t_fd	init_storage(int fd)
{
	t_fd	new;

	new.fdm = fd;
//	new.data = malloc(1);
//	*(new.data) = 0;
	new.data = 0;
	new.next = 0;
	return (new);
}

// umschreiben auf neuen return value von init_storage
t_fd	*get_storage(int fd, t_fd *storage)
{
	t_fd	new;
	t_fd	*previous;
	t_fd	*original;

	original = storage;
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
	new = init_storage(fd);
	if (!original)
		return (&new);
	previous -> next = &new;
	return (storage);
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
	return (line);
}
/*
int main(void)
{
	int fd = open(".test/lorem.txt", O_RDONLY);
	char *text;
	int count = 0;
	printf("fd is: %d, Buffer size is %d\n", fd, BUFFER_SIZE);
//	text = get_next_line(fd);
//	text = get_next_line(fd);
//	prinif (*bytswrtn)tf("line is: %s\n", text);	
	while (text || count == 0)
	{
	        text = get_next_line(fd);
	        count++;
	        printf("%s", text);
//	        printf("the last char is: %d\n", *(text + ft_strlen(text) -1));
	}

	close(fd);
	return (0);
}
*/
