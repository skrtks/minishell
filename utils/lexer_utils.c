/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <skorteka@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 10:37:24 by samkortekaa   #+#    #+#                 */
/*   Updated: 2020/07/02 11:59:11 by skorteka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	set_info(int command, int type, t_node *node)
{
	node->command = command;
	node->type = type;
}

void	continue_populating(char *cmd, t_node *node)
{
	if (!ft_strncmp(cmd, ";", 2))
		set_info(SEMICOLON, SYMBOL, node);
	else if (!ft_strncmp(cmd, "\'", 2))
		set_info(APOSTROPHE, X, node);
	else if (!ft_strncmp(cmd, "\"", 2))
		set_info(QUATATION_MARK, X, node);
	else if (!ft_strncmp(cmd, "<", 2))
		set_info(ARROW_LEFT, REDIRECTION, node);
	else if (!ft_strncmp(cmd, ">", 2))
		set_info(ARROW_RIGHT, REDIRECTION, node);
	else if (!ft_strncmp(cmd, ">>", 3))
		set_info(ARROW_DOUBLE, REDIRECTION, node);
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

int		populate_node(char *cmd, t_node *node)
{
	node->data = ft_strdup(cmd);
	if (!node->data)
	{
		ft_printf("Error parsing command, try again.\n");
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
