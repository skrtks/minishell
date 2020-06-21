/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sam <sam@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/28 15:04:50 by skorteka      #+#    #+#                 */
/*   Updated: 2020/06/20 14:59:25 by sam           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

size_t	get_index(const char *str, char c)
{
	size_t l;

	l = 0;
	while (str[l] != '\0' && str[l] != c)
		l++;
	return (l);
}

char	*ft_strdup2(const char *s1)
{
	char	*new_str;
	size_t	len;
	size_t	i;

	len = get_index(s1, '\0');
	new_str = ft_calloc(len + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_str[i] = s1[i];
		i++;
	}
	return (new_str);
}

char	*ft_substr_gnl(char *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	i;
	char	*str;

	if (s == NULL)
		return (NULL);
	s_len = get_index(s, '\0');
	if (start > s_len)
		return (ft_strdup2(""));
	s_len -= start;
	s_len = (s_len < len) ? s_len : len;
	str = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < s_len && s[start + i] != '\0')
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	free(s);
	return (str);
}
