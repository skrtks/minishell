/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sam <sam@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/18 16:52:43 by sam           #+#    #+#                 */
/*   Updated: 2020/06/18 19:12:52 by sam           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "pipe.h"

t_io *setup_io(t_io *io)
{
	io->fd_read = -1;
	io->fd_write = -1;
	io->ori_stdin = dup(0);
	io->ori_stdout = dup(1);
	io->active = 0;
	io->switch_stdin = 0;
	return (io);
}

t_io *pipe_sequence(t_node *cmd_list, t_io *io)
{
	int *fds;
	int pipe_ahead;

	pipe_ahead = 0;
	fds = malloc(sizeof(int) * 2);
	while (cmd_list && cmd_list->command != SEMICOLON)
	{
		if (cmd_list->command == PIPE)
		{
			pipe_ahead = 1;
			if (io->active)
			{
				close(io->fd_write); // Lijkt geen invloed te hebben
				pipe(fds);
				io->fd_read = fds[0];
				io->fd_write = fds[1];
				close(1);
				dup(io->fd_write);
				if (io->switch_stdin)
				{
					close(0);
					dup(io->fd_read);
				}
				io->switch_stdin = 1;
				break ;
			}
			else {
                pipe(fds);
                io->fd_read = fds[0];
                io->fd_write = fds[1];
                close(1);
                dup(io->fd_write);
                close(0);
                dup(io->fd_read);
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
			close(io->fd_write);
			close(1);
			dup(io->ori_stdout);
			io->active = 0;
			if (io->switch_stdin)
			{
				close(0);
				dup(io->fd_read);
			}
			io->switch_stdin = 1;
		}
		else
		{
			close(io->fd_read);
			close(0);
			dup(io->ori_stdin);
			io->switch_stdin = 0;
		}
	}
	free (fds);
	return (io);
}