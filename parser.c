/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <skorteka@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 14:33:37 by samkortekaa   #+#    #+#                 */
/*   Updated: 2020/06/06 16:35:02 by skorteka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "shell.h"
#include "cd.h"
#include "./libft/libft.h"	

t_node *execute_cmd(t_node *node, t_node *env_list)
{
	if (node->command == ECHO)
	{
		node = node->next;
		write(1, "Executed echo\n", 14);
	}
	else if (node->command == CD)
		node = cd(node);
	else if (node->command == PWD)
	{
		node = node->next;
		write(1, "Executed pwd\n", 13);
	}
	else if (node->command == EXPORT)
	{
		node = node->next;
		write(1, "Executed export\n", 16);
	}
	else if (node->command == UNSET)
	{
		node = node->next;
		write(1, "Executed unset\n", 15);
	}
	else if (node->command == ENV)
		node = env(node, env_list);
	else if (node->command == EXIT)
	{
		node = node->next;
		write(1, "Executed exit\n", 14);
	}
	else
	{
		node = node->next;
		write(1, "Command not recognized\n", 23);
	}
	return (node);
}

void	parse(t_node *cmd_list, t_node *env_list)
{
	t_node *ptr;

	ptr = cmd_list;
	while (ptr)
	{
		ptr = execute_cmd(ptr, env_list);
		if (ptr && ptr->command == SEMICOLON)
			ptr = ptr->next;
	}
}
