/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 13:15:53 by merelmourik   #+#    #+#                 */
/*   Updated: 2020/07/01 15:16:59 by mmourik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft/libft.h"
#include <string.h>
#include "parser.h"

void		reset_std(void)
{
	int std[3];

	dup2(std[0], STDIN_FILENO);		//old, new
	dup2(std[1], STDOUT_FILENO);
	dup2(std[2], STDERR_FILENO);
}

int		open_file(t_node *cmd_list)
{
	if (cmd_list->command == ARROW_RIGHT)
		return (open(cmd_list->next->data, O_RDWR | O_CREAT | O_TRUNC, 0644));
	if (cmd_list->command == ARROW_DOUBLE)
		return (open(cmd_list->next->data, O_RDWR | O_CREAT | O_APPEND, 0644));
	return (0);
}

void	fd_error(void)
{
	reset_std();
	ft_printf("Error: %s\n", strerror(errno));
	errno = 0;
}

void	redirection(t_node *cmd_list, t_lists **list, int i)
{
	int		fd;
	t_node	*ptr;

	ptr = cmd_list;
	while (cmd_list && cmd_list->command != SEMICOLON)
	{
		if (cmd_list->type == REDIRECTION)
		{
			i--;
			if (!(fd = open_file(cmd_list)))
				fd_error();
			if (i > 0)
				close(fd);
		}
		if (i == 0)
		{
			close(1);
			dup(fd);
		}
		cmd_list = cmd_list->next;
	}
	execute_cmd(ptr, list);
	close(fd);
	return ;
}


// als < is ingebouwd, testen hoe hij daarna op > reageert, 
// lijkt alsof de fd niet goed wordt terug gewisseld.