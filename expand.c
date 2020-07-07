/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: sam <sam@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/04 13:58:41 by skorteka      #+#    #+#                 */
/*   Updated: 2020/07/07 16:13:48 by sam           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "lexer.h"
#include "utils/utils.h"

char		*do_expansion(char *word, int i, t_env *env_list)
{
	char *exp;
	
	int id_len;

	if (word[i + 1] == '?')
	{
		exp = ft_itoa(111);
		id_len = 2;
	}
	else
	{
		exp = get_exp(word, i, env_list, &id_len);
		id_len = (word[i] == '~' ? 1 : id_len);
	}
	if (!exp)
		return (NULL);
	char *new_word = update_str(word, i, exp, id_len);
	return (new_word);
}

int len_no_bs(const char *word)
{
	int i;
	int len;

	len = 0;
	i = 0;
	while (word[i])
	{
		if (word[i + 1] == '\\' && word[i] == '\\')
		{
			len++;
			i++;
		}
		else if (word[i] != '\\')
			len++;
		i++;
	}
	return len;
}

char *copy_no_bs(char *word, char *new_word) 
{
	int i;
	int len;

	len = 0;
	i = 0;
	while (word[i])
	{
		if (word[i + 1] == '\\' && word[i] == '\\')
		{
			new_word[len] = word[i];
			len++;
			i++;
		}
		else if (word[i] != '\\')
		{
			new_word[len] = word[i];
			len++;
		}
		i++;
	}
	new_word[len] = '\0';
	free (word);
	return (new_word);
}

char	*remove_backslash(char *word)
{
	int len;
	char *new_word;

	len = len_no_bs(word);
	if (!(new_word = malloc(sizeof(char) * (len + 1))))
	{
		free(word);
		return (NULL);
	}
	new_word = copy_no_bs(word, new_word);
	return (new_word);
}

char			*expand(char *word, t_env *env_list)
{
	int i;

	i = 0;
	while (word[i])
	{
		if ((i == 0 && word[i] == '$') || (i != 0 && word[i] == '$' && word[i - 1] != '\\'))
			word = do_expansion(word, i, env_list);
		else if ((i == 0 && word[i] == '$' && word[i + 1] == '?') || (i != 0 && word[i] == '$' && word[i + 1] == '?' && word[i - 1] != '\\'))
			word = do_expansion(word, i, env_list);
		else if ((i == 0 && word[i] == '~') || (i != 0 && word[i] == '~' && word[i - 1] != '\\'))
			word = do_expansion(word, i, env_list);
		if (!word)
			return (NULL);
		i++;
	}
	word = remove_backslash(word);
	return (word);
}
