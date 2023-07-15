/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:42:14 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/07/15 23:09:46 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif

size_t ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (*str++)
		len++;
	return (len);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	i;

	i = 0;
	if (size > 0)
	{
	        while (i < size - 1 && src[i])
	        {
		                dst[i] = src[i];
		                i++;
	        }
	        dst[i] = 0;
	}
	return (ft_strlen((char *) src));
}


void	ft_bzero(void *s, size_t n)
{
	unsigned long	count;
	char		                *ptr;

	count = 0;
	ptr = (char *) s;
	while (count < n)
	{
	        ptr[count] = 0;
	        count++;
	}
}

int	check_delim(char *input, int flag)
{
	int	i;
	int limit;

	i = 0;
	if (flag)
		limit = ft_strlen(input);
	else
		limit = BUFFER_SIZE;
	while (input[i] && input[i] != '\n' && i < limit)
	        i++;
	if (i == BUFFER_SIZE)
	        return (0);
	else if (input[i] == '\n')
	        return (i + 1);
	else
	        return (-1);
}

char	*get_result(char *src, char *buf)
{
	int	i;
	char *res;

	free(buf);
	i = 0;
	if (!src)
		return (0);
	while (src[i] && src[i] != '\n')
		i++;
	if (src[i] == '\n')
		i++;
	res = malloc(i + 1);
	if (!res)
		return (0);
	ft_strlcpy(res, src, i + 1);
	return (res);
}

char *get_previous(char *buf, char *old, int res, int size)
{
	char *new;

	new = malloc(size + 1);
	if (!new)
		return (0);
	ft_bzero(new, size + 1);
	if (!old)
	{
		old = malloc(1);
		old[0] = 0;
	}
	ft_strlcpy(new, old, ft_strlen(old) + 1);	// new = old
	ft_strlcpy(new + ft_strlen(old), buf, size + 1); // new += buf
//	ft_bzero(buf, res);	        // clean buf
	free(old);
	return (new);
}

char *reset_previous(char *old, int check)
{
	char	*new;

	if (check > 0)
	{
		new = malloc(ft_strlen(old + check));
		if (new)
			ft_strlcpy(new, old + check, ft_strlen(old + check) + 1);
	}
	else if (check <= 0)
		new = 0;
	free(old);
	return (new);
}

char *get_next_line(int fd)
{
	char *buf;
	static char *previous;
	int res;
	int size;
	int count = 0;

	res = BUFFER_SIZE;
	size = 0;
	buf = malloc(BUFFER_SIZE);
	if (!buf)
		return (0);
	while (res == BUFFER_SIZE)
	{
		res = read(fd, buf, BUFFER_SIZE);
//		printf("this is buf: %s\n", buf);
		size += res;
		previous = get_previous(buf, previous, res, size);
		count++;
//		printf("this is buf: %s\n", buf);
		if (check_delim(buf, 0))
			break;
		ft_bzero(buf, BUFFER_SIZE);
	}
	buf = get_result(previous, buf);
	previous = reset_previous(previous, check_delim(previous, 1));
	printf("bytes read in total: %d in %d runs\n", size, count);
	return (buf);
}

int main(void)
{
	int fd = open("lorem.txt", O_RDONLY);
	char *text;
	int count = 0;
	printf("fd is: %d, Buffer size is %d\n", fd, BUFFER_SIZE);
	while (text || count == 0)
	{
		text = get_next_line(fd);
		count++;
		printf("extracted text no. %d: %s\n", count, text);
		printf("the last char is: %d", *(text + ft_strlen(text) -1));
	}	
	close(fd);
	return (0);
}

/*
problems to solve:
	+breaking the loop when '\n' is encountered.
	+how to store the remaining string that has already been read?
	+What should be the loop order?
	-> define the interfaces: what functions do we need and how do they interact?
*/
