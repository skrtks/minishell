/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/02 13:03:24 by samkortekaa   #+#    #+#                 */
/*   Updated: 2020/07/15 10:25:18 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils/utils.h"

static char		*extr_from_brackets(char *input, int *pos, t_env *env_list)
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
		err_msg(NULL, NULL, "Quotes not closed.");
		*pos = -1;
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

static char		*extract_word(char *inp, int *pos, t_env *env_list)
{
	char	*result;
	char	*extr;
	char	*tmp;
	int		from_bracket;

	result = ft_strdup("");
	if (result == NULL)
		return (NULL);
	while ((!ft_strchr(" 	|<>;\0", inp[*pos]) || (inp[*pos] && *pos != 0 \
	&& ft_strchr(" 	|<>;\'\"", inp[*pos]) && inp[*pos - 1] == '\\')))
	{
		from_bracket = 0;
		if ((inp[*pos] == '\'' || inp[*pos] == '\"') && inp[*pos - 1] != '\\')
		{
			if (!(extr = extr_from_brackets(inp, pos, env_list)) || *pos == -1)
				return (clean_and_free(result, extr));
			from_bracket = 1;
		}
		else if (!(extr = extract(inp, pos, env_list, extr)))
			return (clean_and_free(result, extr));
		tmp = ft_strjoin(result, extr);
		clean_and_free(result, extr);
		result = tmp;
	}
	return (extract_result(result, from_bracket, inp[*pos]));
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
		if (inpt[i])
			cmd = extract_word(inpt, &i, env_list);
		if (i == -1)
			return (free_on_error(cmd, head));
		if (cmd)
			if (new_node(&head, cmd))
				return (free_on_error(cmd, head));
		if (check_spec_char("|<>;", inpt[i]))
			if (!set_metachar(&head, inpt, &i))
				return (free_on_error(cmd, head));
		free(cmd);
		cmd = NULL;
	}
	return (head);
}
