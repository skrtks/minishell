/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 13:15:53 by merelmourik   #+#    #+#                 */
/*   Updated: 2020/06/29 09:56:49 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft/libft.h"
#include <string.h>
#include "parser.h"

void		reset_std(void)
{
	int std[3];

	dup2(std[0], STDIN_FILENO);		//old, new
	dup2(std[1], STDOUT_FILENO);
	dup2(std[2], STDERR_FILENO);
}

int		open_file(t_node *cmd_list)
{
	if (cmd_list->command == ARROW_RIGHT)
		return (open(cmd_list->next->data, O_RDWR | O_CREAT | O_TRUNC, 0644));
	if (cmd_list->command == ARROW_DOUBLE)
		return (open(cmd_list->next->data, O_RDWR | O_CREAT | O_APPEND, 0644));
	return (0);
}

void	fd_error(void)
{
	reset_std();
	ft_printf("Error: %s\n", strerror(errno));
	errno = 0;
}

int		count_redirections(t_node *cmd_list)
{
	t_node	*temp;
	int		i;

	i = 0;
	// temp = malloc(sizeof(t_node));		dit is toch veel veiliger?
	temp = cmd_list;
	while (temp)
	{
		if (temp->type == REDIRECTION)
			i++;
		temp = temp->next;
	}
	free(temp);
	return (i);
}

t_node	*redirection(t_node *cmd_list)
{
	int		i;
	int		fd;

	if ((i = count_redirections(cmd_list)) == 0)
		return (cmd_list);
	while (cmd_list && cmd_list->command != SEMICOLON)
	{
		if (cmd_list->type == REDIRECTION)
		{
			i--;
			if (!(fd = open_file(cmd_list)))
				fd_error();
			if (i > 0)
				close(fd);
		}
		if (i == 0)
		{
			close(1);
			dup(fd);
		}
		cmd_list = cmd_list->next;
	}
	// cmd_list = cmd_list->previous;
	return (cmd_list);
}
//lsof -c minishell
