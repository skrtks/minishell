/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <skorteka@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/18 16:52:43 by sam           #+#    #+#                 */
/*   Updated: 2020/07/02 12:37:53 by skorteka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <sys/wait.h>
#include "./libft/libft.h"
#include "lexer.h"
#include "pipe.h"
#include "parser.h"

int setup_pipes(int n_pipes, int **fds)
{
	int i;

	*fds = malloc(sizeof(int) * (n_pipes * 2));
	if (!(*fds))
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

void	child_process(int cmd_index, int *fds, int n_pipes, t_node **ptr)
{
	int pipe_plus;

	check_type(*ptr, &pipe_plus);
	if (cmd_index != 0)
		if (dup2(fds[(cmd_index - 1) * 2], 0) < 0)
			exit_on_error(fds);
	if (cmd_index != n_pipes)
	{
		if (dup2(fds[cmd_index * 2 + 1], 1) < 0)
			exit_on_error(fds);
		if (pipe_plus)
			if (dup2(fds[cmd_index * 2 + 1], 2) < 0)
				exit_on_error(fds);
	}
	close_fds(n_pipes, fds);
}

int execute_in_pipeline(t_node **ptr, int n_pipes, t_lists **list, int *fds)
{
	int	pid;
	int cmd_index;

	cmd_index = 0;
	while ((*ptr) && (*ptr)->command != SEMICOLON) // Update to recognize redirections
	{
		if ((pid = fork()) == -1)
		{
			ft_printf("%s\n", strerror(errno));
			free(fds);
			return (1);
		}
		else if (pid == 0)
		{
			child_process(cmd_index, fds, n_pipes, ptr);
			execute_cmd(*ptr, list);
			exit(1);
		}
        cmd_index = skip_to_cmd(ptr, cmd_index);
    }
	close_fds(n_pipes, fds);
	while ((pid = wait(NULL)) > 0)
		;
	free(fds);
	return (0);
}
