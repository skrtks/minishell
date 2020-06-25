/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sam <sam@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/18 16:52:43 by sam           #+#    #+#                 */
/*   Updated: 2020/06/25 12:54:08 by sam           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "pipe.h"

t_io *setup_io(t_io *io)
{
	io->fd_read = -1;
	io->fd_write = -1;
	io->fd_read_prev = -1;
	io->ori_stdin = dup(0);
	io->ori_stdout = dup(1);
	io->ori_stderr = dup(2);
	io->active = 0;
	return (io);
}

t_io *pipe_sequence(t_node *cmd_list, t_io *io)
{
	int *fds;
	int pipe_ahead;
	int pipe_plus;

	pipe_ahead = 0;
	pipe_plus = 0;
	fds = malloc(sizeof(int) * 2);
	while (cmd_list && cmd_list->command != SEMICOLON)
	{
        if (cmd_list->command == PIPE_PLUS)
            pipe_plus = 1;
		if (cmd_list->command == PIPE || cmd_list->command == PIPE_PLUS)
		{
			pipe_ahead = 1;
			if (io->active)
			{
				if (io->fd_read_prev != -1)
					close(io->fd_read_prev);
				io->fd_read_prev = dup(io->fd_read);
				close(io->fd_write);
				pipe(fds);
				io->fd_read = fds[0];
				io->fd_write = fds[1];
				dup2(io->fd_write, 1);
				dup2(io->fd_read_prev, 0);
				break ;
			}
			else
			{
                pipe(fds);
                io->fd_read = fds[0];
				io->fd_write = fds[1];
				dup2(io->fd_write, 1);
				io->active = 1;
                break ;
            }
		}
        cmd_list = cmd_list->next;
	}
	if (!pipe_ahead)
	{
		if (io->active)
		{
			if (io->fd_read_prev != -1)
				close(io->fd_read_prev);
			close(io->fd_write);
			dup2(io->fd_read, 0);
			dup2(io->ori_stdout, 1);
			io->active = 0;
		}
		else
		{
			close(io->fd_read);
			dup2(io->ori_stdin, 0);
			setup_io(io);
		}
	}
	free (fds);
	return (io);
}