/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 13:15:53 by merelmourik   #+#    #+#                 */
/*   Updated: 2020/07/12 15:09:30 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils/utils.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

static int	clean_exit(int exit, int fd_in, int fd_out, int show_err)
{
	g_exitcode = exit;
	if (fd_in)
		close(fd_in);
	if (fd_out)
		close(fd_out);
	if (show_err)
		err_message(NULL, NULL, strerror(errno));
	return (1);
}

static int	open_file(t_node *cmd_list)
{
	if (cmd_list->command == ARROW_RIGHT)
		return (open(cmd_list->next->data, O_RDWR | O_CREAT | O_TRUNC, 0644));
	if (cmd_list->command == ARROW_DOUBLE)
		return (open(cmd_list->next->data, O_RDWR | O_CREAT | O_APPEND, 0644));
	return (-1);
}

static int	redirect(t_node *cmd_list, int *fd_in, int *fd_out)
{
	struct stat buf;

	if (cmd_list->command == ARROW_LEFT)
		if (stat(cmd_list->next->data, &buf) == -1)
		{
			err_message(NULL, cmd_list->next->data,
					"No such file or directory");
			return (clean_exit(1, *fd_in, *fd_out, 0));
		}
	if (cmd_list->command == ARROW_LEFT)
	{
		if (*fd_in)
			close(*fd_in);
		if (!(*fd_in = open(cmd_list->next->data, O_RDONLY)))
			return (clean_exit(1, *fd_in, *fd_out, 1));
	}
	else
	{
		if (*fd_out)
			close(*fd_out);
		if (!(*fd_out = open_file(cmd_list)))
			return (clean_exit(1, *fd_in, *fd_out, 1));
	}
	return (0);
}

int			redirection(t_node *cmd_list)
{
	int		fd_out;
	int		fd_in;

	fd_in = -1;
	fd_out = -1;
	if (cmd_list->type == REDIR && cmd_list->next == NULL)
		return (1);
	while (cmd_list && cmd_list->command != SEMICOLON)
	{
		if (cmd_list->type == REDIR)
			if (redirect(cmd_list, &fd_in, &fd_out) == 1)
				return (1);
		cmd_list = cmd_list->next;
	}
	if (fd_in != -1)
		if ((dup2(fd_in, 0)) < 0)
			return (clean_exit(9, fd_in, fd_out, 1));
	if (fd_out != -1)
		if ((dup2(fd_out, 1)) < 0)
			return (clean_exit(9, fd_in, fd_out, 1));
	g_exitcode = 0;
	return (0);
}
