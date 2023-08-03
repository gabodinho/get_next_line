/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 16:08:13 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/08/03 17:46:24 by ggiertzu         ###   ########.fr       */
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
	fd = open("files/alternate_line_nl_no_nl", O_RDONLY);
	while (text)
	{
		text = get_next_line(fd);
		printf("%s", text);
		free(text);
	}
	close(fd);
	return (0);
}

