/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/27 16:08:36 by sam           #+#    #+#                 */
/*   Updated: 2020/07/03 11:39:17 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "lexer.h"
#include "utils/utils.h"

static int	clean(char *str, char *str1, char *str2, int ret_code)
{
	if (str)
		free(str);
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	return (ret_code);
}

static int	do_expan(t_node *cmd_ptr, char *id_str, t_env *env_list, int id_len)
{
	char *id;
	char *repl_str;
	char *tmp;

	if (!(id = ft_substr(id_str, 0, id_len)))
		return (1);
	while (env_list)
	{
		if (!ft_strncmp(env_list->data, id, id_len) &&
			env_list->data[id_len] == '=')
		{
			if (!(repl_str = ft_substr(env_list->data, id_len + 1,
								ft_strlen(env_list->data + id_len + 1))))
				return (clean(id, NULL, NULL, 1));
			tmp = ft_strdup(cmd_ptr->data);
			free(cmd_ptr->data);
			if (!(cmd_ptr->data = ft_strjoin(repl_str, tmp)))
				return (clean(id, repl_str, tmp, 1));
			clean(repl_str, tmp, NULL, 0);
			break ;
		}
		env_list = env_list->next;
	}
	free(id);
	return (0);
}

static int	do_tilde_expansion(t_node *cmd_ptr, t_env *env_list)
{
	char *path;
	char *repl_str;

	if (cmd_ptr->data[1] != '\0' && ft_strchr("@^*+[]{},.?", cmd_ptr->data[1]))
		return (0);
	path = NULL;
	while (env_list)
	{
		if (!ft_strncmp("HOME=", env_list->data, 5))
		{
			if (!(path = ft_strdup(env_list->data + 5)))
				return (1);
			break ;
		}
		env_list = env_list->next;
	}
	if (!(repl_str = ft_strjoin(path, cmd_ptr->data + 1)))
		return (clean(path, NULL, NULL, 1));
	free(cmd_ptr->data);
	cmd_ptr->data = repl_str;
	if (path)
		free(path);
	return (0);
}

int			expand(t_node *node, t_env *env_list)
{
	int		id_len;
	char	*id_str;
	t_node	*cmd_ptr;
	t_env	*env_head;

	cmd_ptr = node;
	env_head = env_list;
	while (cmd_ptr)
	{
		env_list = env_head;
		if (cmd_ptr->data[0] == '$' && cmd_ptr->data[1] == '\0')
			return (0);
		if (cmd_ptr->data[0] == '~')
		{
			if (do_tilde_expansion(cmd_ptr, env_list))
				return (1);
		}
		else if (cmd_ptr->data[0] == '$')
		{
			id_len = get_len(cmd_ptr->data + 1);
			if (!(id_str = ft_strdup(cmd_ptr->data + 1)))
				return (1);
			free(cmd_ptr->data);
			cmd_ptr->data = ft_strdup(id_str + id_len);
			if (do_expan(cmd_ptr, id_str, env_list, id_len))
				return (clean(id_str, NULL, NULL, 1));
			free(id_str);
		}
		cmd_ptr = cmd_ptr->next;
	}
	return (0);
}
