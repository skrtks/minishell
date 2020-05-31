/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/29 15:00:32 by merelmourik   #+#    #+#                 */
/*   Updated: 2020/05/31 20:33:34 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	word_count(char const *s)
{
	int		i;
	int		co;

	co = 0;
	i = 0;
	if (*s == 0)
		return (0);
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && s[i] == ';')
			i++;
		if (s[i] != '\0' && s[i] != ';')
		{
			co++;
			while (s[i] != '\0' && s[i] != ';')
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

static char	*word(char const *s)
{
	char	*word;
	int		i;

	i = 0;
	while (s[i] == ' ')
		i++;
	int j = i;
	while (s[i] != '\0' && s[i] != ';' && s[i] != ' ')
		i++;
	word = (char*)malloc(sizeof(char) * (i - j + 1));
	if (word == NULL)
		return (NULL);
	i = 0;
	while (s[j + i] != ';' && s[j + i] != '\0' && s[j + i] != ' ')
	{
		word[i] = s[j + i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static char	**new_string(char const *s, char **arr)
{
	int i;

	i = 0;
	while (*s)
	{
		while (*s == ';' && *s)
			s++;
		if (*s != ';' && *s)
		{
			arr[i] = word(s);
			if (arr[i] == NULL)
				return (ft_free(i, arr));
			i++;
			while (*s != ';' && *s)
				s++;
		}
	}
	return (arr);
}

char		**ft_split(char const *s)
{
	char	**arr;

	if (s == NULL)
		return (NULL);
	arr = (char **)malloc(sizeof(char *) * (word_count(s) + 1));
	if (arr == NULL)
		return (NULL);
	arr = new_string(s, arr);
	arr[word_count(s)] = NULL;
	return (arr);
}

// static int	word_count(char const *s)
// {
// 	int		i;
// 	int		co;

// 	co = 1;
// 	i = 0;
// 	if (*s == 0)
// 		return (0);					//error handling
// 	while (s[i] != '\0')			//of niet gelijk is aan enter? (10)
// 	{
// 		if (s[i] == ';')
// 			co++;
// 		i++;
// 	}
// 	return (co);
// }

// static void	*ft_free(int i, char **word)
// {
// 	while (i != 0)
// 	{
// 		i--;
// 		if (word[i])
// 			free(word[i]);
// 	}
// 	free(word);
// 	return (NULL);
// }

// static char	*word(char const *str)
// {
// 	char	*word;
// 	int		i;

// 	i = 0;
// 	while (str[i] != '\0' && str[i] != ';')
// 		i++;
// 	word = (char*)malloc(sizeof(char) * (i + 1));
// 	if (word == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (str[i] != ';' && str[i] != '\0')
// 	{
// 		word[i] = str[i];
// 		i++;
// 	}
// 	word[i] = '\0';
// 	return (word);
// }

// static char	**new_string(char const *str, char **arr)
// {
// 	int i;

// 	i = 0;

// 	while (*str)
// 	{
// 		if (*str != ';')
// 		{
// 			arr[i] = word(str);
// 			if (arr[i] == NULL)
// 				return (ft_free(i, arr));
// 			i++;
// 			while (*str != ';' && *str)
// 				str++;
// 			str++;
// 		}
// 	}
// 	return (arr);
// }

// char		**ft_split(char const *str)
// {
// 	char	**arr;

// 	if (str == NULL)
// 		return (NULL);
// 	arr = (char **)malloc(sizeof(char *) * (word_count(str)));
// 	if (arr == NULL)
// 		return (NULL);
// 	arr = new_string(str, arr);
// 	arr[word_count(str)] = NULL;
// 	int i = 0;
// 	while (arr[1][i])
// 	{
// 		write(1, &arr[0][i], 1);
// 		i++;
// 	}
// 	write(1, "\n", 1);
// 	return (arr);
// }
