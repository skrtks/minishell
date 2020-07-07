/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sam <sam@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/07 14:25:50 by sam           #+#    #+#                 */
/*   Updated: 2020/07/07 14:27:33 by sam           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "lexer.h"
#include "utils/utils.h"

char	*clean(char *str, char *str1, char *str2)
{
	if (str)
		free(str);
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	return (NULL);
}
char		*get_env_string(t_env *env_list, const int *id_len, const char *id, char *exp)
{
	while (env_list)
	{
		if (!ft_strncmp(id + 1, env_list->data, *id_len - 1) &&
			env_list->data[*id_len - 1] == '=')
		{
			free(exp);
			exp = ft_strdup(env_list->data + *id_len + 1);
			break ;
		}
		env_list = env_list->next;
	}
	return exp;
}
char		*get_exp(char *word, int i, t_env *env_list, int *id_len)
{
	char *id;
	char *exp;
	t_env *head;

	head = env_list;
	*id_len = 1;
	while (ft_isalpha(word[i + *id_len]) || word[i + *id_len] == '_')
		(*id_len)++;
	id = (word[i] == '~' ? ft_strdup("$HOME") : ft_substr(word + i, 0, *id_len));
	*id_len = (word[i] == '~' ? 5 : *id_len);
	exp = (*id_len == 1 ? ft_strdup("$") : ft_strdup(""));
	if (!id || !exp)
		return (clean(NULL, id, exp));
	exp = get_env_string(env_list, id_len, id, exp);
	env_list = head;
	free(id);
	return (exp);
}
char		*update_str(char *word, int i, char *exp, int id_len)
{
	char *before_str;
	char *after_str;
	char *new_word;

	before_str = ft_substr(word, 0, i);
	if (!before_str)
		return (NULL);
	after_str = ft_substr(word, i + id_len, (ft_strlen(word) - i));
	if (!after_str)
		return (clean(NULL, NULL, before_str));
	new_word = ft_strjoin(before_str, exp);
	if (!new_word)
		return (clean(NULL, before_str, after_str));
	free(before_str);
	before_str = ft_strjoin(new_word, after_str);
	if (!before_str)
		return (clean(NULL, after_str, new_word));
	free(new_word);
	free(after_str);
	free(word);
	free(exp);
	return (before_str);
}
