/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   next_line.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/29 11:43:11 by merelmourik   #+#    #+#                 */
/*   Updated: 2020/06/06 12:13:27 by mmourik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "./libft/libft.h"

#define BUFF_SIZE 1024

static char	*ft_realloc(char *input, int size)
{
	char *tmp_str;

	tmp_str = ft_strdup(input);
	if (!tmp_str)
		exit(1);
	free(input);
	input = malloc(sizeof(char) * size);
	if (!input)
		exit(1);
	input = tmp_str;
	return (input);
}

static int		ft_read(int fd, char **input)
{
	char	*buffer;
	int		ret;
	int		buff_size;

	buff_size = BUFF_SIZE;
	buffer = malloc(sizeof(char) * BUFF_SIZE);
	if (buffer == NULL)
	{
		free(input);
		return (-2);
	}
	ret = read(fd, buffer, (buff_size - 1));
	if (ret >= BUFF_SIZE)
		while (ret >= buff_size)
		{
			buff_size += BUFF_SIZE;
			buffer = ft_realloc(buffer, buff_size);
			ret = read(fd, buffer, (buff_size - 1));
		}
	if (ret == -1)
	{
		free(*input);
		free(buffer);
		return (-2);
	}
	ret--;
	buffer[ret] = '\0';
	*input = ft_strjoin(*input, buffer);
	if (input == NULL)
	{
		free(buffer);
		return (-2);
	}
	free(buffer);
	return (ret);
}

int			next_line(int fd, char **input)
{
	int ret;

	*input = ft_strdup("");
	if (input == NULL)
		return (-2);
	ret = ft_read(fd, input);			
	return ((ret == -2) ? -1 : 0);
}
