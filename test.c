#include <unistd.h>
#include <stdio.h>
#include "libft/libft.h"

#define BUF_SIZE 1024

char *ft_realloc(char *input, int size)
{
	char *tmp_str;

	tmp_str = ft_strdup(input);
	if (!tmp_str)
		exit (1);
	free(input);
	input = malloc(sizeof(char) * size);
	if (!input)
		exit (1);
	input = tmp_str;
	return (input);
}

char *get_input(int fd) 
{
	int buf_size;
	int pos;
	int c;
	int ret;
	char *buffer;

	buf_size = BUF_SIZE;
	buffer = malloc(sizeof(char) * buf_size);
	if (!buffer)
		exit (1);

	pos = 0;
	c = 0;
	while (1)
	{
		ret = read(fd, &c, 1);
		if (ret < 0)
		{
			printf("Error on read\n");
			exit (2);
		}
		else if (ret == 0 || c == '\n')
		{
			buffer[pos] = '\0';
			return (buffer);
		}
		else
		{
			printf("c = %d\n", c);
			buffer[pos] = c;
		}
		pos++;
		if (pos >= buf_size)
		{
			buf_size += BUF_SIZE;
			buffer = ft_realloc(buffer, buf_size);
		}
	}
	return 0;
}

int main(void)
{
	int   ret;
	char *buffer;

	ret = 1;

	while (1)
	{
		write(1, "> $ ", 4);
		buffer = get_input(0);
		printf("+++ %s +++\n", buffer);
	}
	return 0;
}