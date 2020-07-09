/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 13:15:53 by merelmourik   #+#    #+#                 */
/*   Updated: 2020/07/07 21:42:57 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft/libft.h"
#include <string.h>
#include <sys/stat.h>
#include "parser.h"

int			count_redirections(t_node *cmd_list)
{
	t_node	*temp;

	temp = cmd_list;
	while (temp)
	{
		if (temp->type == REDIR)
			return (1);
		temp = temp->next;
	}
	return (0);
}

static int	open_file(t_node *cmd_list)
{
	if (cmd_list->command == ARROW_RIGHT)
		return (open(cmd_list->next->data, O_RDWR | O_CREAT | O_TRUNC, 0644));
	if (cmd_list->command == ARROW_DOUBLE)
		return (open(cmd_list->next->data, O_RDWR | O_CREAT | O_APPEND, 0644));
	return (-1);
}

int		fd_error(void)
{
	ft_printf("Error: %s\n", strerror(errno));
	g_exitcode = 2;
	errno = 0;
	return (1);
}

static int	redirect(t_node *cmd_list, int *fd_in, int *fd_out)
{
	struct stat buf;

	if (cmd_list->command == ARROW_LEFT)
		if (stat(cmd_list->next->data, &buf) == -1)
		{
			ft_printf("minishell: %s: No such file or directory\n", cmd_list->next->data);
			return (1); // Exit code? in bash 1 bij deze error
		}
	if (cmd_list->command == ARROW_LEFT)
	{
		if (*fd_in)
			close(*fd_in);
		if (!(*fd_in = open(cmd_list->next->data, O_RDONLY)))
			return (fd_error());
	}
	else
	{
		if (*fd_out)
			close(*fd_out);
		if (!(*fd_out = open_file(cmd_list)))
			return (fd_error());
	}
	return (0);
}

int redirection(t_node *cmd_list)
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
		if (!(dup2(fd_in, 0)))
			errno = 0; // Waarom errno op 0?
	if (fd_out != -1)
		if (!(dup2(fd_out, 1)))
			errno = 0; // Waarom errno op 0?
	return (0);
}
