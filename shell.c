/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/29 11:46:04 by merelmourik   #+#    #+#                 */
/*   Updated: 2020/06/04 13:11:24 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "lexer.h"

int main(void)
{
	int		ret;
	char	*input;
	node_t	*command_list;
	
	while (1)
	{
		write(1, "minishell> $ ", 13);
		ret = next_line(0, &input);
		if (ret == -1)
		{
			errno = 0;
			break ;
		}
		command_list = lexer(input);
		node_t *ptr = command_list;
		while (ptr)
		{
			printf("command %i, type %i, data %s\n", ptr->command, ptr->type, ptr->data);
			ptr = ptr->next;
		}
		free_list(&command_list);
	}
	return (0);
}