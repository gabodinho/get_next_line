/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:42:14 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/07/15 22:47:27 by ggiertzu         ###   ########.fr       */
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

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned long	i;
	unsigned long	j;
	unsigned long	size_dst;

	i = 0;
	j = 0;
	size_dst = ft_strlen(dst);
	while (dst[i] && i < size)
	        i++;
	while (src[j] && size > j + i + 1)
	{
	        dst[i + j] = src[j];
	        j++;
	}
	if (i == size)
	        return (ft_strlen(src) + size);
	else
	{
	        dst[i + j] = 0;
	        return (size_dst + ft_strlen(src));
	}
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
int test_read(int fd, void *buf)
{
	return (read(fd, buf, BUFFER_SIZE));
}

int main(void)
{
	int fd = open("lorem.txt", O_RDONLY);
	printf("fd is: %d, Buffer size is %d\n", fd, BUFFER_SIZE);
	char *text;
	char *buf = malloc(BUFFER_SIZE);
	static char *previous;
	if (!previous)
	{
		previous = malloc(1);
		previous[0] = 0;
	}
	int res = BUFFER_SIZE;
	int count = 0;
	int size = 0;
	text = 0;
	while (res == BUFFER_SIZE)
	{
		res = test_read(fd, buf);
		printf("this is buf: %s\n", buf);
		size += res;
		text = malloc(size + 1);
		ft_strlcpy(text, previous, ft_strlen(previous) + 1);	// text = previous + buf;
		ft_strlcpy(text + ft_strlen(previous), buf, size + 1); 
		ft_bzero(buf, res);		// clean the buffer 
		free(previous);
		previous = malloc(size + 1);
		ft_strlcpy(previous, text, size + 1);
		free(text);
		count++;
	}
	free(buf);
	printf("bytes read in total: %d in %d runs\ntext read: %s\n", size, count, previous);
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
