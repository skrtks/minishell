/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <skorteka@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 14:33:37 by samkortekaa   #+#    #+#                 */
/*   Updated: 2020/06/06 13:08:06 by skorteka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "./libft/libft.h"	

t_node *execute_cmd(t_node *ptr)
{
	if (ptr->command == ECHO)
	{
		ptr = ptr->next;
		write(1, "Executed echo\n", 14);
	}
	else if (ptr->command == CD)
	{
		ptr = ptr->next;
		write(1, "Executed cd\n", 12);
	}
	else if (ptr->command == PWD)
	{
		ptr = ptr->next;
		write(1, "Executed pwd\n", 13);
	}
	else if (ptr->command == EXPORT)
	{
		ptr = ptr->next;
		write(1, "Executed export\n", 16);
	}
	else if (ptr->command == UNSET)
	{
		ptr = ptr->next;
		write(1, "Executed unset\n", 15);
	}
	else if (ptr->command == ENV)
	{
		ptr = ptr->next;
		write(1, "Executed env\n", 13);
	}
	else if (ptr->command == EXIT)
	{
		ptr = ptr->next;
		write(1, "Executed exit\n", 14);
	}
	else
	{
		ptr = ptr->next;
		write(1, "Command not recognized\n", 23);
	}
	return (ptr);
}

void	parse(t_node *cmd_list)
{
	t_node *ptr;

	ptr = cmd_list;
	while (ptr)
	{
		ptr = execute_cmd(ptr);
		if (ptr && ptr->command == SEMICOLON)
			ptr = ptr->next;
	}
}
