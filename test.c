/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 16:08:13 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/08/05 11:14:39 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line_bonus.h"
#include <sys/stat.h>
#include <fcntl.h>


int main(void)
{
	char *text;
	int fd;

	text = "test";
	fd = open("files/a_nl.txt", O_RDONLY);
	int fd2 = open("files/b_nl.txt", O_RDONLY);
	int fd3 = open("files/c_nl.txt", O_RDONLY);
	while (text)
	{
		text = get_next_line(fd);
		printf("%s", text);
		free(text);
		text = get_next_line(fd2);
		printf("%s", text);
 		free(text);
		text = get_next_line(fd2);
		printf("%s", text);
 		free(text);
		text = get_next_line(fd3);
		printf("%s", text);
 		free(text);
	}
	close(fd);
	fd = open("files/a_nl.txt", O_RDONLY);
	text  = get_next_line(fd);
	free(text);
	close(fd);
	close(fd2);
	close(fd3);
	return (0);
}

