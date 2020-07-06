/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/02 13:03:24 by samkortekaa   #+#    #+#                 */
/*   Updated: 2020/07/06 14:46:41 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "lexer.h"
#include "utils/utils.h"

static char		*extract_from_brackets(const char *input, int *pos) // TODO: Implement how other spec chars are handled.
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
	return (extr);
}

static char		*extract_word(char *input, int *pos)
{
	char	*extr;
	int		len;

	if ((input[*pos] == '\''
		|| input[*pos] == '\"') && input[*pos - 1] != '\\')
		return (extract_from_brackets(input, pos));
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

t_node			*invalid_input(char *str, t_node **head)
{
	if (str[0] == '<' && str[1] == '|' && str[2] == '|')
		ft_printf("minishell: syntax error near unexpected token `||'\n");
	else if ((str[0] == '|' && str[1] != '|') || \
		(str[0] == '<' && str[1] == '|'))
		ft_printf("minishell: syntax error near unexpected token `|'\n");
	else if (str[0] == '|' && str[1] == '|')
		ft_printf("minishell: syntax error near unexpected token `||'\n");
	else if (str[0] == ';' && str[1] != ';')
		ft_printf("minishell: syntax error near unexpected token `;'\n");
	else if (str[0] == ';' && str[1] == ';')
		ft_printf("minishell: syntax error near unexpected token `;;'\n");
	else if (str[0] == '<' && str[1] == '<' && str[2] == '|' && str[3] == '|')
		ft_printf("minishell: syntax error near unexpected token `||'\n");
	else if (str[0] == '<' && str[1] == '<' && str[2] == '|')
		ft_printf("minishell: syntax error near unexpected token `|'\n");
	return (*head);
}

t_node			*lexer(char *input)
{
	int		i;
	char	*cmd;
	t_node	*head;

	i = 0;
	head = NULL;
	if (input[0] == '|' || input[0] == ';' || input[0] == '<')
		return (invalid_input(input, &head));
	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		if (!(cmd = extract_word(input, &i)))
			return (free_on_error(cmd, head));
		if (cmd[0])
			if (new_node(&head, cmd))
				return (free_on_error(cmd, head));
		if (check_spec_char("|<>;", input[i]))
		{
			if (!set_metachar(&head, input, &i))
				return (free_on_error(cmd, head));
		}
		free(cmd);
	}
	return (head);
}
