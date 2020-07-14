/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 10:37:24 by samkortekaa   #+#    #+#                 */
/*   Updated: 2020/07/14 14:12:40 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void	set_info(int command, int type, t_node *node)
{
	node->command = command;
	node->type = type;
}

char		*extract_result(char *result, int from_bracket)
{
	if (!result[0] && !from_bracket)
	{
		free(result);
		return (NULL);
	}
	return (result);
}

static void	continue_populating(char *cmd, t_node *node)
{
	if (!ft_strncmp(cmd, ";", 2))
		set_info(SEMICOLON, SYMBOL, node);
	else if (!ft_strncmp(cmd, "\'", 2))
		set_info(APOSTROPHE, X, node);
	else if (!ft_strncmp(cmd, "\"", 2))
		set_info(QUATATION_MARK, X, node);
	else if (!ft_strncmp(cmd, "<", 2))
		set_info(ARROW_LEFT, REDIR, node);
	else if (!ft_strncmp(cmd, ">", 2))
		set_info(ARROW_RIGHT, REDIR, node);
	else if (!ft_strncmp(cmd, ">>", 3))
		set_info(ARROW_DOUBLE, REDIR, node);
	else if (!ft_strncmp(cmd, "|&", 3))
		set_info(PIPE_PLUS, SYMBOL, node);
	else if (!ft_strncmp(cmd, "|", 2))
		set_info(PIPE, SYMBOL, node);
	else if (!ft_strncmp(cmd, "$", 2))
		set_info(DOLLAR, X, node);
	else if (!ft_strncmp(cmd, "$?", 3))
		set_info(DOLLAR_QUESTION, X, node);
	else if (!ft_strncmp(cmd, "./", 2) || !ft_strncmp(cmd, "/", 1))
		set_info(EXECUTABLE, COMMAND, node);
	else
		set_info(OTHER, ARGUMENT, node);
}

int			populate_node(char *cmd, t_node *node)
{
	node->data = ft_strdup(cmd);
	if (!node->data)
	{
		g_exitcode = 12;
		return (1);
	}
	if (!ft_strncmp(cmd, "echo", 5))
		set_info(ECHO, COMMAND, node);
	else if (!ft_strncmp(cmd, "cd", 3))
		set_info(CD, COMMAND, node);
	else if (!ft_strncmp(cmd, "pwd", 4))
		set_info(PWD, COMMAND, node);
	else if (!ft_strncmp(cmd, "export", 7))
		set_info(EXPORT, COMMAND, node);
	else if (!ft_strncmp(cmd, "unset", 6))
		set_info(UNSET, COMMAND, node);
	else if (!ft_strncmp(cmd, "env", 4))
		set_info(ENV, COMMAND, node);
	else if (!ft_strncmp(cmd, "exit", 5))
		set_info(EXIT, COMMAND, node);
	else if (!ft_strncmp(cmd, "-n", 3))
		set_info(N, FLAG, node);
	else
		continue_populating(cmd, node);
	return (0);
}

int			set_metachar(t_node **head, char *input, int *pos)
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
