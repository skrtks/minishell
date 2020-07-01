/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: sam <sam@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/27 16:08:36 by sam           #+#    #+#                 */
/*   Updated: 2020/07/01 10:52:27 by sam           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "lexer.h"

// TODO: Bij input met ${ x} worden twee nodes aangemaakt met ${ en x}. Dat moet even anders.

int check_braces(char *str)
{
    int i;

    i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '}' && str[i - 1] != '\\')
			return (i);
		if (ft_strchr("@^*+[]:,./?~ ", str[i]))
		{
			ft_printf("minishell: ${%s: bad substitution\n", str);
			return (-1);
		}
		i++;
	}
	ft_printf("Braces not closed\n");
    return (-1);
}

int get_len(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr("@^*+[]:,./?~ ", str[i]))
			return (i);
		i++;
	}
	return (i);
}

int do_expansion(t_node *cmd_ptr, char *id_str, t_env *env_list, int id_len)
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
			{
				free(id);
				return (1);
			}
			tmp = ft_strdup(cmd_ptr->data);
			free(cmd_ptr->data);
			if (!(cmd_ptr->data = ft_strjoin(repl_str, tmp)))
			{
				free(id);
				free(repl_str);
				free(tmp);
				return (1);
			}
			free(repl_str);
			free(tmp);
			break ;
		}
		env_list = env_list->next;
	}
	free(id);
	return (0);
}

int expand(t_node *node, t_env *env_list)
{
	int id_len;
	t_node *cmd_ptr;
	t_env *env_head;
	char *id_str;

	cmd_ptr = node;
	env_head = env_list;
	while (cmd_ptr) // Update to support pipes etc)
	{
		env_list = env_head;
		if (cmd_ptr->data[0] == '$' && cmd_ptr->data[1] == '\0')
			return (0);
		if (cmd_ptr->data[0] == '$' && cmd_ptr->data[1] == '{')
		{
			if ((id_len = check_braces(cmd_ptr->data + 2)) == -1)
				return (1);
			if (!(id_str = ft_strdup(cmd_ptr->data + 2)))
				return (1);
			free (cmd_ptr->data);
			cmd_ptr->data = ft_strdup(id_str + id_len + 1);
			if (do_expansion(cmd_ptr, id_str, env_list, id_len))
			{
				free(id_str);
				return (1);
			}
			free (id_str);
		}
		else if (cmd_ptr->data[0] == '$')
		{
			id_len = get_len(cmd_ptr->data + 1);
			if (!(id_str = ft_strdup(cmd_ptr->data + 1)))
					return (1);
			free (cmd_ptr->data);
			cmd_ptr->data = ft_strdup(id_str + id_len);
			if (do_expansion(cmd_ptr, id_str, env_list, id_len))
			{
				free(id_str);
				return (1);
			}
			free (id_str);
		}
		cmd_ptr = cmd_ptr->next;
	}
	return (0);
}