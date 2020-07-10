/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 14:33:37 by samkortekaa   #+#    #+#                 */
/*   Updated: 2020/07/10 11:52:44 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins/builtins.h"
#include "parser.h"
#include "lexer.h"
#include "execute.h"
#include "pipe.h"

t_node	*execute_cmd(t_node *node, t_lists **list)
{
	if (node->command == ECHO)
		node = echo(node);
	else if (node->command == CD)
		node = cd(node, list);
	else if (node->command == PWD)
		node = pwd(node);
	else if (node->command == EXPORT)
		node = export_cmd(node, list);
	else if (node->command == UNSET)
		node = unset(node, list);
	else if (node->command == ENV)
		node = env(node, (*list)->env_list);
	else if (node->command == EXECUTABLE)
		node = execute(node, (*list)->env_list);
	else if (node->command == DOLLAR_QUESTION)
		node = exit_code(node);
	else if (node->command == EXIT)
		exit_shell(node, &(*list)->env_list, &(*list)->export_list, 0);
	else
	{
		if (check_for_path(&(node)->data, (*list)->env_list))
			node = execute(node, (*list)->env_list);
		else
		{
            ft_printf("minishell: %s: Command not found\n", node->data);
			node = node->next;
			g_exitcode = 127;
		}
	}
	if (node && node->type == REDIR)
		while (node && node->type != SYMBOL)
			node = node->next;
	return (node);
}

void	parse(t_node *cmd_list, t_lists **list)
{
	t_node	*ptr;
	int		n_pipes;
	int		*fds;
	int		ori_out;
	int		ori_in;

	ori_out = dup(1);
	ori_in = dup(0);
	ptr = cmd_list;
	while (ptr)
	{
		n_pipes = count_pipes(ptr);
		if (redirection(ptr) != 1)
		{
			if (n_pipes && ptr)
			{
				if (setup_pipes(n_pipes, &fds))
					return ;
				execute_in_pipe(&ptr, n_pipes, list, fds);
			}
			else if (ptr)
				ptr = execute_cmd(ptr, list);
		}
		else
			while (ptr && ptr->command != SEMICOLON)
				ptr = ptr->next;
		if (ptr && (ptr->type == SYMBOL || ptr->type == REDIR))
			ptr = ptr->next;
	}
	dup2(ori_out, 1);
	dup2(ori_in, 0);
}
