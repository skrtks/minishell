/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 13:15:53 by merelmourik   #+#    #+#                 */
/*   Updated: 2020/06/22 07:06:53 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

#include <fcntl.h>
#include "libft/libft.h"
#include <stdio.h>
#include <string.h>
#include "parser.h"

t_fd		*setup_fd(t_fd *fd)
{
	fd->active = 0;
	fd->fd_write = -1;
	fd->fd_read = -1;
	fd->fd_error = -1;
	return (fd);
}

void		reset_std(int *std)
{
	dup2(std[0], STDIN_FILENO);
	dup2(std[1], STDOUT_FILENO);
	dup2(std[2], STDERR_FILENO);
}

int		open_file(t_node *cmd_list)
{
	if (cmd_list->command == ARROW_RIGHT)
		return (open(cmd_list->next->data, O_RDWR | O_CREAT | O_TRUNC, 0677));
	if (cmd_list->command == ARROW_DOUBLE)
		return (open(cmd_list->next->data, O_RDWR | O_CREAT | O_APPEND, 0677));
	return (0);
}

void	redirection(t_node *cmd_list, t_fd *fd)
{
	int std[3];

	while (cmd_list && cmd_list->command != SEMICOLON)
	{
		if (cmd_list->type == SYMBOL)
			{
				if (!(fd->fd_write = open_file(cmd_list)))
				{
					reset_fd(std);
					ft_printf("Error: %s\n", strerror(errno));
					errno = 0;
				}
				close(1);
				dup(fd->fd_write);
		}
		cmd_list = cmd_list->next;
	}
	fd->active = 1;
}