/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 18:37:52 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/08/03 12:47:38 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "get_next_line.h"

int main(void)
{
	int count = 0;
	int fd = open("files/big_line_with_nl", O_RDONLY);
	char *text = "test"; 
	while (text)
	{
		text = get_next_line(fd);
		printf("%s", text);
		count++;
	}
	return (0);
}


