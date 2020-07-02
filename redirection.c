/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 13:15:53 by merelmourik   #+#    #+#                 */
/*   Updated: 2020/07/02 19:45:39 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft/libft.h"
#include <string.h>
#include "parser.h"

int		count_redirections(t_node *cmd_list)
{
	t_node	*temp;
	int		i;

	i = 0;
	temp = cmd_list;
	while (temp)
	{
		if (temp->type == REDIRECTION)
			i++;
		temp = temp->next;
	}
	free(temp);
	return (i);
}

int		open_file(t_node *cmd_list)
{
	if (cmd_list->command == ARROW_RIGHT)
		return (open(cmd_list->next->data, O_RDWR | O_CREAT | O_TRUNC, 0644));
	if (cmd_list->command == ARROW_DOUBLE)
		return (open(cmd_list->next->data, O_RDWR | O_CREAT | O_APPEND, 0644));
	return (0);			//error van maken
}

void	fd_error(void)
{
	ft_printf("Error: %s\n", strerror(errno));
	errno = 0;
}

void	redirection(t_node *cmd_list)
{
	int		fd_out;
	int		fd_in;

	while (cmd_list && cmd_list->command != SEMICOLON)
	{
		if (cmd_list->type == REDIRECTION)
		{
			if (cmd_list->command == ARROW_LEFT)
			{
				if (fd_in)
					close(fd_in);		//ook beschermen
				if (!(fd_in = open(cmd_list->next->data, O_RDONLY)))
					fd_error();
			}
			else
			{
				if (fd_out)
					close(fd_out);
				if (!(fd_out = open_file(cmd_list)))
					fd_error();
			}
		}
		cmd_list = cmd_list->next;
	}
	dup2(fd_in, 0);		//zou eigenlijk met if statement moeten denk ik
	dup2(fd_out, 1);
}
