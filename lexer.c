/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/02 13:03:24 by samkortekaa   #+#    #+#                 */
/*   Updated: 2020/07/07 15:46:25 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "lexer.h"
#include "utils/utils.h"
#include "expand.h"

static char		*extract_from_brackets(const char *input, int *pos)
{
	char	b_type;
	char	*extr;
	int		len;
	int		start;

	b_type = input[*pos];
	*pos += 1;
	start = *pos;
	len = *pos;
	while (input[len] && (input[len] != b_type
			|| (input[len] == b_type && input[len - 1] == '\\')))
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
    expand(&extr, env_list);
	return (extr);
}

static char		*extract_word(char *input, int *pos,
							t_env *env_list)
{
	char	*extr;
	int		len;

	if ((input[*pos] == '\''
		|| input[*pos] == '\"') && input[*pos - 1] != '\\')
		return (extract_from_brackets(input, pos, env_list));
	len = *pos;
	while (!ft_strchr(" 	|<>;\'\"\0", input[len]) ||
			(len != 0 && ft_strchr(" 	|<>;\'\"", input[len]) &&
			input[len - 1] == '\\'))
		len++;
	len -= *pos;
	extr = ft_substr_lexer(input, *pos, len);
	if (!extr)
		return (NULL);
	*pos += len;
	expand(&extr, env_list);
	return (extr);
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

static int		set_metachar(t_node **head, char *input, int *pos)
{
	int err;

	err = 0;
	if (!ft_strncmp(input + *pos, "|&", 2))
	{
		err = new_node(head, "|&");
		(*pos)++;
	}
	else if (!ft_strncmp(input + *pos, "|", 1))
		err = new_node(head, "|");
	else if (!ft_strncmp(input + *pos, ">>", 2))
	{
		err = new_node(head, ">>");
		(*pos)++;
	}
	else if (!ft_strncmp(input + *pos, ">", 1))
		err = new_node(head, ">");
	else if (!ft_strncmp(input + *pos, "<", 1))
		err = new_node(head, "<");
	else if (!ft_strncmp(input + *pos, ";", 1))
		err = new_node(head, ";");
	(*pos)++;
	if (!err)
		return (1);
	return (0);
}

t_node			*lexer(char *inpt)
{
	int		i;
	char	*cmd;
	t_node	*head;

	i = 0;
	head = NULL;
	if (inpt[0] == '|' || inpt[0] == ';' || (inpt[0] == '>' && inpt[1] == '>'))
		return (invalid_input(inpt, &head));
	while (inpt[i])
	{
		while (inpt[i] == ' ')
			i++;
		if (!(cmd = extract_word(inpt, &i)))
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
