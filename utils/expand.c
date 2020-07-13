/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/04 13:58:41 by skorteka      #+#    #+#                 */
/*   Updated: 2020/07/12 12:18:54 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static char	*do_expansion(char *word, int *i, t_env *env_list)
{
	char	*exp;
	int 	exp_len;
	char	*new_word;
	int		id_len;

	if (word[*i + 1] == '?')
	{
		exp = ft_itoa(g_exitcode);
		id_len = 2;
	}
	else
	{
		exp = get_exp(word, *i, env_list, &id_len);
		id_len = (word[*i] == '~' ? 1 : id_len);
	}
	if (!exp)
		return (NULL);
	exp_len = ft_strlen(exp);
	new_word = update_str(word, *i, exp, id_len);
	*i += exp_len;
	return (new_word);
}

static int	len_no_bs(const char *word, int in_quotes)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while (word[i])
	{
		if (word[i + 1] == '\\' && word[i] == '\\')
		{
			len++;
			i++;
		}
		else if (word[i] != '\\' || (in_quotes && (word[i + 1] != '$') &&
				word[i + 1] != '\"'))
			len++;
		i++;
	}
	return (len);
}

static char	*copy_no_bs(char *word, char *new_word, int in_quotes)
{
	int	i;
	int	len;

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
		else if (word[i] != '\\' || (in_quotes && (word[i + 1] != '$') &&
				word[i + 1] != '\"'))
		{
			new_word[len] = word[i];
			len++;
		}
		i++;
	}
	new_word[len] = '\0';
	free(word);
	return (new_word);
}

static char	*remove_backslash(char *word, int in_quotes)
{
	int		len;
	char	*new_word;

	len = len_no_bs(word, in_quotes);
	if (!(new_word = malloc(sizeof(char) * (len + 1))))
	{
		free(word);
		return (NULL);
	}
	new_word = copy_no_bs(word, new_word, in_quotes);
	return (new_word);
}

char		*expand(char *word, t_env *env_list, int in_quotes)
{
	int		i;
	int		word_len;

	i = 0;
	while (word[i])
	{
		if ((i == 0 && word[i] == '$') || (i != 0 && word[i] == '$' &&
			word[i - 1] != '\\'))
			word = do_expansion(word, &i, env_list);
		else if ((i == 0 && word[i] == '$' && word[i + 1] == '?') || (i != 0 &&
				word[i] == '$' && word[i + 1] == '?' && word[i - 1] != '\\'))
			word = do_expansion(word, &i, env_list);
		else if (!in_quotes && ((i == 0 && word[i] == '~') ||
				(i != 0 && word[i] == '~' && word[i - 1] != '\\')))
			word = do_expansion(word, &i, env_list);
		else
			i++;
		if (!word)
			return (NULL);
	}
	word = remove_backslash(word, in_quotes);
	return (word);
}
