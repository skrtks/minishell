/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/02 13:03:24 by samkortekaa   #+#    #+#                 */
/*   Updated: 2020/07/12 11:23:51 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*extract_from_brackets(char *input, int *pos, t_env *env_list)
{
	char	b_type;
	char	*extr;
	int		len;

	b_type = input[*pos];
	*pos += 1;
	len = *pos;
	while (input[len] && (input[len] != b_type || (b_type != '\'' && \
		input[len] == b_type && input[len - 1] == '\\')))
		len++;
	if (input[len] != b_type)
	{
		ft_printf("Quotes not closed.\n");
		return (NULL);
	}
	len -= *pos;
	extr = ft_substr(input, *pos, len);
	if (!extr)
		return (NULL);
	*pos += len + 1;
	if (b_type == '\"')
		extr = expand(extr, env_list, 1);
	return (extr);
}

static char		*extract(char *input, int *pos, t_env *env_list, char *extr)
{
	int len;

	len = *pos;
	while (!ft_strchr(" 	|<>;\'\"\0", input[len]) || (input[len] && len \
	!= 0 && ft_strchr(" 	|<>;\'\"", input[len]) && input[len - 1] == '\\'))
		len++;
	len -= *pos;
	if (!(extr = ft_substr(input, *pos, len)))
		return (NULL);
	*pos += len;
	if (!(extr = expand(extr, env_list, 0)))
		return (NULL);
	return (extr);
}

static char		*extract_word(char *input, int *pos, t_env *env_list)
{
	char	*result;
	char	*extr;
	char	*tmp;

	if (!(result = ft_strdup("")))
		return (NULL);
	while ((!ft_strchr(" 	|<>;\0", input[*pos]) || (input[*pos] && \
	*pos != 0 && ft_strchr(" 	|<>;\'\"", input[*pos]) && \
	input[*pos - 1] == '\\')))
	{
		if ((input[*pos] == '\'' || input[*pos] == '\"') && \
		input[*pos - 1] != '\\')
		{
			if (!(extr = extract_from_brackets(input, pos, env_list)))
				return (clean_and_free(tmp, result, extr));
		}
		else if (!(extr = extract(input, pos, env_list, extr)))
			return (clean_and_free(tmp, result, extr));
		tmp = ft_strjoin(result, extr);
		clean_and_free(result, extr, NULL);
		result = tmp;
	}
	return (result);
}

int				new_node(t_node **head, char *cmd)
{
	t_node *new_node;
	t_node *ptr;

	ptr = *head;
	if (!(new_node = malloc(sizeof(t_node))))
		return (1);
	if (populate_node(cmd, new_node))
	{
		free(new_node);
		return (1);
	}
	new_node->next = NULL;
	if (!(*head))
	{
		new_node->previous = NULL;
		*head = new_node;
		return (0);
	}
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new_node;
	new_node->previous = ptr;
	return (0);
}

t_node			*lexer(char *inpt, t_env *env_list)
{
	int		i;
	char	*cmd;
	t_node	*head;

	i = 0;
	head = NULL;
	while (inpt[i])
	{
		while (inpt[i] == ' ')
			i++;
		if (!(cmd = extract_word(inpt, &i, env_list)))
			return (free_on_error(cmd, head));
		if (cmd[0])
			if (new_node(&head, cmd))
				return (free_on_error(cmd, head));
		if (check_spec_char("|<>;", inpt[i]))
		{
			if (!set_metachar(&head, inpt, &i))
				return (free_on_error(cmd, head));
		}
		free(cmd);
	}
	return (head);
}
