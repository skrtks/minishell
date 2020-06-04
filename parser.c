/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: samkortekaas <samkortekaas@student.codam.nl> +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 14:33:37 by samkortekaas  #+#    #+#                 */
/*   Updated: 2020/06/04 15:40:56 by samkortekaas  ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"

void execute_cmd(node_t *ptr)
{
	if (ptr->command == ECHO)
		write(1, "Executed echo\n", 14);
	else if (ptr->command == CD)
		write(1, "Executed cd\n", 12);
	else if (ptr->command == PWD)
		write(1, "Executed pwd\n", 13);
	else if (ptr->command == EXPORT)
		write(1, "Executed export\n", 16);
	else if (ptr->command == EXIT)
		write(1, "Executed exit\n", 14);
	else
		write(1, "Command not recognized\n", 23);
}

void parse(node_t *cmd_list)
{
	node_t *ptr;

	ptr = cmd_list;
	while (ptr)
	{
		if (ptr->type == COMMAND)
			execute_cmd(ptr);
		else
			write(1, "Command not recognized\n", 23);
		ptr = ptr->next;
	}
}