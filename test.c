#include<stdio.h>
#include<unistd.h>
#include"get_next_line.h"

int main(void)
{
	int fd = open("big_line_with_nl", O_RDONLY);
	char *text = 0;
	int count = 0;

	while (!count || text)
	{
		text = get_next_line(fd);
		printf("%s", text);
		count++;
	}
	return (0);
}
