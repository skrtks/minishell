/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 14:33:37 by samkortekaa   #+#    #+#                 */
/*   Updated: 2020/06/11 18:14:59 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "echo.h"
#include "shell.h"
#include "exit.h"
#include "cd.h"
#include "./libft/libft.h"

t_node	*execute_cmd(t_node *node, t_lists **list)
{
	if (node->command == ECHO)
		node = echo(node);
	else if (node->command == CD)
		node = cd(node, (*list)->env_list);
	else if (node->command == PWD)
		node = pwd(node);
	else if (node->command == EXPORT)
		node = export_cmd(node, &(*list)->export_list, &(*list)->env_list);
	else if (node->command == UNSET)
	{
		node = node->next;
		write(1, "Executed unset\n", 15);
	}
	else if (node->command == ENV)
		node = env(node, (*list)->env_list);
	else if (node->command == EXIT)
		exit_shell(node, &(*list)->env_list, &(*list)->export_list, 0);
	else
	{
		node = node->next;
		write(1, "Command not recognized\n", 23);
	}
	return (node);
}

void	parse(t_node *cmd_list, t_lists **list)
{
	t_node *ptr;

	ptr = cmd_list;
	while (ptr)
	{
		ptr = execute_cmd(ptr, list);
		if (ptr && ptr->command == SEMICOLON)
			ptr = ptr->next;
	}
}
