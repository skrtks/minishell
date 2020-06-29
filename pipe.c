/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/18 16:52:43 by sam           #+#    #+#                 */
/*   Updated: 2020/06/29 09:22:57 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <sys/wait.h>
#include "./libft/libft.h"
#include "lexer.h"
#include "pipe.h"
#include "parser.h"

int count_pipes(t_node *cmd_list)
{
	int n;

	n = 0;
	while (cmd_list && cmd_list->command != SEMICOLON)
	{
		if (cmd_list->command == PIPE || cmd_list->command == PIPE_PLUS)
			n++;
		cmd_list = cmd_list->next;
	}
	return (n);
}

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

void exit_on_error(int *fds)
{
	if (fds)
		free(fds);
	ft_printf("%s\n", strerror(errno));
	exit(1);
}

void close_fds(int n_pipes, const int *fds) 
{
	int i;

	i = 0;
	while (i < (2 * n_pipes))
	{
		close(fds[i]);
		i++;
	}
}

void check_type(t_node *ptr, int *type)
{
	while (ptr && ptr->command != PIPE && ptr->command != PIPE_PLUS
			&& ptr->command != SEMICOLON) // Update to recognize redirections
			ptr = ptr->next;
	if (ptr && ptr->command == PIPE_PLUS)
		*type = 1;
	else
		*type = 0;
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
		while (*ptr && (*ptr)->command != PIPE && (*ptr)->command != PIPE_PLUS
				&& (*ptr)->command != SEMICOLON)
			*ptr = (*ptr)->next;		//update for redirections
		if (*ptr && ((*ptr)->command == PIPE_PLUS || (*ptr)->command == PIPE))
			*ptr = (*ptr)->next;
		cmd_index++;
	}
	close_fds(n_pipes, fds);
	while ((pid = wait(NULL)) > 0)
		;
	free(fds);
	return (0);
}
