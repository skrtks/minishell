/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 14:33:37 by samkortekaa   #+#    #+#                 */
/*   Updated: 2020/06/28 22:03:15 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins/builtins.h"
#include "parser.h"
#include "lexer.h"
#include "execute.h"
#include "./libft/libft.h"
#include "pipe.h"

static t_node	*execute_cmd(t_node *node, t_lists **list)
{
	if (node->command == ECHO)
		node = echo(node);
	else if (node->command == CD)
		node = cd(node, (*list)->env_list);
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
	else if (node->command == EXIT)
		exit_shell(node, &(*list)->env_list, &(*list)->export_list, 0);
	else
	{
		if (check_for_path(&(node)->data, (*list)->env_list))
			node = execute(node, (*list)->env_list);
		else
		{
			node = node->next; // Skip to end or next semicolon
			write(1, "Command not recognized\n", 23);
		}
	}
	return (node);
}

void		reset_fd(int *std)
{
	dup2(std[0], STDIN_FILENO);
	dup2(std[1], STDOUT_FILENO);
	dup2(std[2], STDERR_FILENO);
}

void	parse(t_node *cmd_list, t_lists **list, t_io *io)
{
	t_node *ptr;
	int std[3];

	ptr = cmd_list;		//waarom geven we niet gewoon de cmd_list mee?
	while (ptr)
	{
		io = pipe_sequence(ptr, io);
		redirection(ptr);
		ptr = execute_cmd(ptr, list);
		if (ptr && ptr->type == SYMBOL)
			ptr = ptr->next;
	}
	reset_fd(std);
    // io = pipe_sequence(ptr, io);
}
