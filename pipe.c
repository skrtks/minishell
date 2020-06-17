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
#include "libft/libft.h"
#include <string.h>

t_io *set_up_pipe(void)
{
	t_io	*io;

	io = malloc(sizeof(t_io));
	io->stdin = malloc(sizeof(int));
	*io->stdin = 0;
	io->stdout = malloc(sizeof(int));
	*io->stdout = 0;
	io->pipe_fd = malloc(sizeof(int) * 2);
	io->old_in = malloc(sizeof(int));
	io->old_out = malloc(sizeof(int));
	if (pipe(io->pipe_fd) == -1)
	{
		ft_printf("%s", strerror(errno));
		return (NULL);
	}
	ft_printf("Pipe fd's set up\n"); // Weghalen
	return (io);
}

int pipe_out(t_io *io)
{
	*io->old_out = dup(1);
	close(1);
	dup2(io->pipe_fd[0], 1);
	return (0);
}

int pipe_in(t_io *io)
{
	*io->old_in = dup(0);
	close(0);
	dup2(io->pipe_fd[1], 0);
	return (0);
}

int reset_out(t_io *io)
{
	close(1);
	dup2(*io->old_out, 1);
	return (0);
}

int reset_in(t_io *io)
{
	close(0);
	dup2(*io->old_in, 0);
	return (0);
}

int set_pipes(t_node *cmd_list, int *pipe_before, t_io *io)
{
	if (*io->stdout)
	{
		reset_out(io);
		*io->stdout = 0;
		ft_printf("Reset out\n");
	}
	if (*io->stdin && *pipe_before)
	{
		reset_in(io);
		*io->stdin = 0;
		ft_printf("Reset in\n");
	}
	if (*pipe_before)
	{
		ft_printf("Set stdin\n");
		pipe_in(io);
		*io->stdin = 1;
	}
	while (cmd_list) {
		if (cmd_list->command == PIPE)
		{
			ft_printf("Set stdout\n");
			pipe_out(io);
			*io->stdout = 1;
			break ;
		}
		cmd_list = cmd_list->next;
	}
	*pipe_before = 0;
	return (1);
}
