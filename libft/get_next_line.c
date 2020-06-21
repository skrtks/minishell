/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sam <sam@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/25 09:40:16 by skorteka      #+#    #+#                 */
/*   Updated: 2020/06/20 16:17:10 by sam           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static ssize_t	join_output(char **s1, char *s2, int nl_index)
{
	int		i;
	int		j;
	char	*new_str;

	new_str = ft_calloc(get_index(*s1, '\0') + get_index(s2, '\n') + 1,
						sizeof(char));
	if (!new_str)
		return (-1);
	i = 0;
	while ((*s1)[i])
	{
		new_str[i] = (*s1)[i];
		i++;
	}
	j = 0;
	while (j < nl_index)
	{
		new_str[i] = s2[j];
		i++;
		j++;
	}
	new_str[i] = '\0';
	free(*s1);
	*s1 = new_str;
	return (j);
}

static ssize_t	scan_next_line(int fd, char **buf, char **line, char **result)
{
	ssize_t		read_out;
	ssize_t		nl_index;
	ssize_t		b_index;

	nl_index = get_index(*buf, '\n');
	b_index = 0;
	while (b_index <= nl_index)
	{
		if ((*buf)[b_index] == '\0')
		{
			read_out = read(fd, *buf, BUFFER_SIZE);
			if (read_out <= 0)
			{
				*line = *result;
				return (read_out < 0 ? -1 : 0);
			}
			nl_index = get_index(*buf, '\n');
			b_index = 0;
			(*buf)[read_out] = '\0';
		}
		b_index = join_output(result, *buf, nl_index);
		if ((*buf)[b_index] == '\n' || b_index == -1)
			break ;
	}
	return (b_index == -1 ? -1 : 1);
}

int				free_obj(char **result, char **buf, char **line)
{
	if (*buf)
	{
		free(*buf);
		*buf = NULL;
	}
	if (result && *result != *line)
		free(result);
	return (-1);
}

int				get_next_line(int fd, char **line)
{
	static char *buf;
	char		*result;
	ssize_t		nl_index;
	ssize_t		read_out;

	if (read(fd, 0, 0) == -1)
		return (-1);
	if (!buf)
		buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	result = ft_calloc(1, sizeof(char));
	if (!buf || !result)
		return (free_obj(&result, &buf, line));
	read_out = scan_next_line(fd, &buf, line, &result);
	if (read_out <= 0)
	{
		free_obj(&result, &buf, line);
		return (read_out < 0 ? -1 : 0);
	}
	nl_index = get_index(buf, '\n');
	buf = ft_substr_gnl(buf, nl_index + 1, get_index(buf + nl_index + 1, '\0'));
	if (!buf)
		return (free_obj(&result, &buf, line));
	*line = result;
	return (1);
}
