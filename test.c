/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 18:37:52 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/08/01 21:30:54 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "get_next_line.h"

int main(void)
{
	int count = 0;
	int fd = open("big_line_with_nl", O_RDONLY);
	char *text = "test"; 
	while (text)
	{
		text = get_next_line(0);
		printf("%s", text);
		count++;
	}
	return (0);
}


