/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: sam <sam@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 14:33:37 by samkortekaa   #+#    #+#                 */
/*   Updated: 2020/06/17 17:01:05 by sam           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins/builtins.h"
#include "parser.h"
#include "lexer.h"
#include "execute.h"
#include "./libft/libft.h"
#include "pipe.h"
#include <string.h>

static t_node	*execute_cmd(t_node *node, t_lists **list, t_io *io)
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
		exit_shell(node, &(*list)->env_list, &(*list)->export_list, io);
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

void	parse(t_node *cmd_list, t_lists **list, t_io *io)
{
	t_node 	*ptr;
	int		pipe_before;

	ptr = cmd_list;
	pipe_before = 0;
	// ft_printf("read %i / write %i\n", io.pipe_fd[0], io.pipe_fd[1]);
	// close(io.pipe_fd[0]);
	// close(io.pipe_fd[1]);
	// free (fds);
	while (ptr)
	{
		set_pipes(ptr, &pipe_before, io);
		ptr = execute_cmd(ptr, list, io);
		if (ptr && ptr->command == SEMICOLON)
			ptr = ptr->next;
		else if (ptr && ptr->command == PIPE)
		{
			pipe_before = 1;
			ptr = ptr->next;
		}
	}
	set_pipes(ptr, &pipe_before, io);
}
