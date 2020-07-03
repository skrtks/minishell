/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_extract_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <skorteka@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 12:12:40 by skorteka      #+#    #+#                 */
/*   Updated: 2020/07/03 12:14:54 by skorteka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft/libft.h"

size_t	ft_strlen_lexer(const char *str)
{
	size_t l;
	int		i;

	l = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != '\\')
			l++;
		i++;
	}
	return (l);
}

char *cpy_str(char *str, const char *s, int start, int s_len)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < s_len && s[start + j] != '\0')
	{
		if (s[start + j] != '\\')
		{
			str[i] = s[start + j];
			i++;
		}
		j++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_substr_lexer(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*str;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen_lexer(s);
	if (start > s_len)
		return (ft_strdup(""));
	s_len -= start;
	s_len = (s_len < len) ? s_len : len;
	str = malloc((s_len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str = cpy_str(str, s, start, s_len);
	return (str);
}