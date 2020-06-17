/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sam <sam@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/17 16:28:43 by sam           #+#    #+#                 */
/*   Updated: 2020/06/17 16:59:19 by sam           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include "lexer.h"

int set_pipes(t_node *cmd_list, int *pipe_before)
{
	(void)pipe_before;
	while (cmd_list) {
		if (cmd_list->command == PIPE)
		{
			printf("Pipe found\n");
		}
		cmd_list = cmd_list->next;
	}
	return (1);
}
