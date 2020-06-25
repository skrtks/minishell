/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sam <sam@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/18 16:52:43 by sam           #+#    #+#                 */
/*   Updated: 2020/06/25 15:40:21 by sam           ########   odam.nl         */
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

void no_ahead(t_io *io)
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

void new_ahead(t_io *io, int pipe_plus)
{
    int *fds;
    (void)pipe_plus;
    fds = malloc(sizeof(int) * 2);
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
    }
    else
    {
        pipe(fds);
        io->fd_read = fds[0];
        io->fd_write = fds[1];
        dup2(io->fd_write, 1);
        io->active = 1;
    }
    free (fds);
}

t_io *pipe_sequence(t_node *cmd_list, t_io *io)
{
	int pipe_ahead;
	int pipe_plus;

	pipe_ahead = 0;
	pipe_plus = 0;
	while (cmd_list && cmd_list->command != SEMICOLON)
	{
        if (cmd_list->command == PIPE_PLUS)
            pipe_plus = 1;
		if (cmd_list->command == PIPE || cmd_list->command == PIPE_PLUS)
		{
			pipe_ahead = 1;
            new_ahead(io, pipe_plus);
            break ;
		}
        cmd_list = cmd_list->next;
	}
	if (!pipe_ahead)
	{
        no_ahead(io);
    }
	return (io);
}