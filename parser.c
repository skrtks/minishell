/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <skorteka@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 14:33:37 by samkortekaa   #+#    #+#                 */
/*   Updated: 2020/06/05 15:43:18 by skorteka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"

void	execute_cmd(t_node *ptr)
{
	if (ptr->command == ECHO)
		write(1, "Executed echo\n", 14);		//hoe koppelen we -n eraan
	else if (ptr->command == CD)
		write(1, "Executed cd\n", 12);
	else if (ptr->command == PWD)
		write(1, "Executed pwd\n", 13);
	else if (ptr->command == EXPORT)
		write(1, "Executed export\n", 16);
	else if (ptr->command == UNSET)
		write(1, "Executed unset\n", 15);
	else if (ptr->command == ENV)
		write(1, "Executed env\n", 13);
	else if (ptr->command == EXIT)
		write(1, "Executed exit\n", 14);
	else
		write(1, "Command not recognized\n", 23);
}

void	parse(t_node *cmd_list)
{
	t_node *ptr;

	ptr = cmd_list;
	while (ptr)
	{
		if (ptr->type == COMMAND)
			execute_cmd(ptr);
		else			//is deze nodig? misschien error van maken
			write(1, "Command not recognized\n", 23);
		ptr = ptr->next;
	}
}
