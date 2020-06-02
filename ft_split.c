/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/29 15:00:32 by merelmourik   #+#    #+#                 */
/*   Updated: 2020/06/02 09:54:52 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	word_count(char const *str)
{
	int		i;
	int		co;

	co = 0;
	i = 0;
	if (*str == 0)
		return (0);
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && str[i] == ';')
			i++;
		if (str[i] != '\0' && str[i] != ';')
		{
			co++;
			while (str[i] != '\0' && str[i] != ';')
				i++;
		}
	}
	return (co);
}

static void	*ft_free(int i, char **word)
{
	while (i != 0)
	{
		i--;
		if (word[i])
			free(word[i]);
	}
	free(word);
	return (NULL);
}

static char	*word(char const *str)
{
	char	*word;
	int		i;

	i = 0;
	while (str[i] == ' ')
		i++;
	int j = i;
	while (str[i] != '\0' && str[i] != ';' && str[i] != ' ')
		i++;
	word = (char*)malloc(sizeof(char) * (i - j + 1));
	if (word == NULL)
		return (NULL);
	i = 0;
	while (str[j + i] != ';' && str[j + i] != '\0' && str[j + i] != ' ')
	{
		word[i] = str[j + i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static char	**new_string(char const *str, char **arr)
{
	int i;

	i = 0;
	while (*str)
	{
		while (*str == ';' && *str)
			str++;
		if (*str != ';' && *str)
		{
			arr[i] = word(str);
			if (arr[i] == NULL)
				return (ft_free(i, arr));
			i++;
			while (*str != ';' && *str)
				str++;
		}
	}
	return (arr);
}

char		**ft_split(char const *str)
{
	char	**arr;

	if (str == NULL)
		return (NULL);
	arr = (char **)malloc(sizeof(char *) * (word_count(str) + 1));
	if (arr == NULL)
		return (NULL);
	arr = new_string(str, arr);
	arr[word_count(str)] = NULL;
	return (arr);
}
