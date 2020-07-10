/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/18 16:52:43 by sam           #+#    #+#                 */
/*   Updated: 2020/07/10 11:13:22 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <sys/wait.h>
#include "./libft/libft.h"
#include "lexer.h"
#include "pipe.h"
#include "parser.h"

int			setup_pipes(int n_pipes, int **fds)
{
	int i;

	if (!(*fds = malloc(sizeof(int) * (n_pipes * 2))))
		return (1);
	i = 0;
	while (i < n_pipes)
	{
		if (pipe((*fds) + i * 2) < 0)
		{
			ft_printf("%s\n", strerror(errno));
			free((*fds));
			return (1);
		}
		i++;
	}
	return (0);
}

static int	child_process(int cmd_index, int *fds, int n_pipes, t_node **ptr)
{
	int pipe_plus;

	check_type(*ptr, &pipe_plus);
	if (cmd_index != 0)
		if (dup2(fds[(cmd_index - 1) * 2], 0) < 0)
			return (-1);
	if (cmd_index != n_pipes)
	{
		if (dup2(fds[cmd_index * 2 + 1], 1) < 0)
			return (-1);
		if (pipe_plus)
			if (dup2(fds[cmd_index * 2 + 1], 2) < 0)
				return (-1);
	}
	close_fds(n_pipes, fds);
	return (0);
}

void	exit_on_error(int *fds)
{
	if (fds)
		free(fds);
	ft_printf("%s\n", strerror(errno));
	exit(1);
}

t_node			*clean_exit_pipe(t_node **ptr, int exit_code, int *fds)
{
	if (exit_code == 10)
		ft_printf("%s\n", strerror(errno));
	g_exitcode = exit_code;
	free(fds);
	while (*ptr && (*ptr)->command != SEMICOLON)
		*ptr = (*ptr)->next;
	return (*ptr);
}

t_node		*execute_in_pipe(t_node **ptr, int npipe, t_lists **list, int *fds)
{
	int	pid;
	int cmd_index;

	cmd_index = 0;
	while (*ptr && (*ptr)->command != SEMICOLON && (*ptr)->command != REDIR)
	{
		if ((pid = fork()) == -1)
			return (clean_exit_pipe(ptr, 10, fds));
		else if (pid == 0)
		{
			if (child_process(cmd_index, fds, npipe, ptr) == -1)
				return (clean_exit_pipe(ptr, 9, fds));
			execute_cmd(*ptr, list);
			exit(g_exitcode);
		}
		cmd_index = skip_to_cmd(ptr, cmd_index);
	}
	close_fds(npipe, fds);
	while ((pid = wait(NULL)) > 0)
		;
	return (clean_exit_pipe(ptr, 0, fds));
}
