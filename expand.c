/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <skorteka@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/04 13:58:41 by skorteka      #+#    #+#                 */
/*   Updated: 2020/07/04 16:31:37 by skorteka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "lexer.h"
#include "utils/utils.h"

// static int	clean(char *str, char *str1, char *str2, int ret_code)
// {
// 	if (str)
// 		free(str);
// 	if (str1)
// 		free(str1);
// 	if (str2)
// 		free(str2);
// 	return (ret_code);
// }

// Implement error checking

char *get_exp(char *word, int i, t_env *env_list, int *id_len)
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
	env_list = head;
	free(id);
	return (exp);
}

char *do_expansion(char *word, int i, t_env *env_list)
{
	char *exp;
	char *before_str;
	char *after_str;
	char *new_word;
	int id_len;

	exp = get_exp(word, i, env_list, &id_len);
    id_len = (word[i] == '~' ? 1 : id_len);
    before_str = ft_substr(word, 0, i);
    after_str = ft_substr(word, i + id_len, (ft_strlen(word) - i));
    new_word = ft_strjoin(before_str, exp);
    free(before_str);
    before_str = ft_strjoin(new_word, after_str);
    free(new_word);
    free(after_str);
    free(word);
    free(exp);
    new_word = before_str;
	return (new_word);
}

int			expand(char **word_in, t_env *env_list)
{
	char *word;
	int i;

	word = *word_in;
	i = 0;
	while (word[i])
	{
		if ((i == 0 && word[i] == '$') || (i != 0 && word[i] == '$' && word[i - 1] != '\\'))
			word = do_expansion(word, i, env_list);
		else if ((i == 0 && word[i] == '~') || (i != 0 && word[i] == '~' && word[i - 1] != '\\'))
            word = do_expansion(word, i, env_list);
		if (!word)
			return (1);
		i++;
	}
	*word_in = word;
	return (0);
}
