/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   next_line.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/29 11:43:11 by merelmourik   #+#    #+#                 */
/*   Updated: 2020/05/29 14:52:34 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		ft_strlen(char *str)
{
	int i;
	
	i = 0;
	while (str[i])
		i++;
	return (i);
}

static char	*ft_dup(char *str)
{
	int		i;
	char	*dup;
	i = ft_strlen(str);
	if (!(dup = malloc(sizeof(char) * (i + 1))))
		return NULL;
	i = 0;
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

static char		*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*new;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	new = malloc(sizeof(char) * (i + j + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		new[i + j] = s2[j];
		j++;
	}
	new[i + j] = '\0';
	free(s1);
	return (new);
}

static int		ft_read(int fd, char **input)
{
	char	*buffer;
	int		ret;

	buffer = malloc(sizeof(char) * 1024);
	if (buffer == NULL)
	{
		free(input);
		return (-2);
	}
	ret = read(fd, buffer, 1023);
	if (ret == -1)
	{
		free (*input);
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
	
	*input = ft_dup("");
	if (input == NULL)
		return (-2);
	ret = ft_read(fd, input);
	return ((ret == -2) ? -1 : 0);
}
