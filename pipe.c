/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <skorteka@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/18 16:52:43 by sam           #+#    #+#                 */
/*   Updated: 2020/06/19 13:27:33 by skorteka      ########   odam.nl         */
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
	io->ori_stderr = dup(2);
	io->active = 0;
	io->switch_stdin = 0;
	return (io);
}
 
t_io *pipe_sequence(t_node *cmd_list, t_io *io)
{
	int *fds;
	int pipe_ahead;
	// int pipe_plus;

	pipe_ahead = 0;
	// pipe_plus = 0;
	fds = malloc(sizeof(int) * 2);
	while (cmd_list && cmd_list->command != SEMICOLON)
	{
        // if (cmd_list->command == PIPE_PLUS)
        //     pipe_plus = 1;
		if (cmd_list->command == PIPE || cmd_list->command == PIPE_PLUS)
		{
			pipe_ahead = 1;
			if (io->active)
			{
				close(io->fd_write);
				close(io->fd_read);
				pipe(fds);
				io->fd_read = fds[0];
				io->fd_write = fds[1];
				close(1);
				dup(io->fd_write);
				// if (pipe_plus)
				// {
				// 	close(2);
				// 	dup(io->fd_write);
				// }
				if (io->switch_stdin)
				{
					close(0);
					dup(io->fd_read);
				}
				io->switch_stdin = 1;
				break ;
			}
			else 
			{
                pipe(fds);
                io->fd_read = fds[0];
                io->fd_write = fds[1];
                close(1);
                dup(io->fd_write);
    //             if (pipe_plus)
				// {
				// 	close(2);
				// 	dup(io->fd_write);
				// }
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
			close(2);
			dup(io->ori_stderr);
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