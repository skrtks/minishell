/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   next_line.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/29 11:43:11 by merelmourik   #+#    #+#                 */
/*   Updated: 2020/06/05 17:02:45 by mmourik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "./libft/libft.h"

static char	*ft_realloc(char *input, int size)
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

static int	ft_read(int fd, char **input)
{
	char	*buffer;
	int		ret;
	int		pos;

	pos = 0;
	while (1)
	{
		buffer = malloc(sizeof(char) * 1024);			//kan dus maar een x aantal characters lezen
		if (buffer == NULL)
		{
			free(input);
			return (-2);
		}
		ret = read(fd, buffer, 1023);
		if (ret == 0 || buffer[pos] == '\n')
			return (ret);
		if (ret == -1)
		{
			free(*input);
			free(buffer);
			return (-2);
		}
		ret--;
		buffer[ret] = '\0';
		*input = ft_strjoin(*input, buffer);
		free(buffer);
		if (input == NULL)
			return (-2);
		pos++;
		if (pos >= 1024)
			buffer = ft_realloc(buffer, 1024);
	}
	return (0);
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
