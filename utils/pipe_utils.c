/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/27 13:30:21 by sam           #+#    #+#                 */
/*   Updated: 2020/07/09 20:27:15 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "lexer.h"
#include "pipe.h"

int		count_pipes(t_node *cmd_list)
{
	int n;

	n = 0;
	while (cmd_list && cmd_list->command != SEMICOLON)
	{
		if (cmd_list->command == PIPE || cmd_list->command == PIPE_PLUS)
			n++;
		cmd_list = cmd_list->next;
	}
	return (n);
}

void	close_fds(int n_pipes, const int *fds)
{
	int i;

	i = 0;
	while (i < (2 * n_pipes))
	{
		close(fds[i]);
		i++;
	}
}

void	check_type(t_node *ptr, int *type)
{
	while (ptr && ptr->command != PIPE && ptr->command != PIPE_PLUS \
			&& ptr->command != SEMICOLON)
		ptr = ptr->next;
	if (ptr && ptr->command == PIPE_PLUS)
		*type = 1;
	else
		*type = 0;
}

int		skip_to_cmd(t_node **ptr, int cmd_index)
{
	while (*ptr && (*ptr)->command != PIPE && (*ptr)->command != PIPE_PLUS \
			&& (*ptr)->command != SEMICOLON)
		*ptr = (*ptr)->next;
	if (*ptr && ((*ptr)->command == PIPE_PLUS || (*ptr)->command == PIPE))
		*ptr = (*ptr)->next;
	cmd_index++;
	return (cmd_index);
}
