/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <skorteka@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 13:15:53 by merelmourik   #+#    #+#                 */
/*   Updated: 2020/07/02 13:01:35 by skorteka      ########   odam.nl         */
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
	// temp = malloc(sizeof(t_node));		dit is toch veel veiliger?
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
	return (0);
}

void	fd_error(void)
{
	ft_printf("Error: %s\n", strerror(errno));
	errno = 0;
}

void	redirection(t_node *cmd_list, t_lists **list, int i)
{
	int		fd;
	int		ori_in;
	t_node	*ptr;

	ori_in = dup(1);
	ptr = cmd_list;
	while (cmd_list && cmd_list->command != SEMICOLON) // Stop veranderen
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
	dup2(ori_in, 1);
	return ;
}


// als < is ingebouwd, testen hoe hij daarna op > reageert, 
// lijkt alsof de fd niet goed wordt terug gewisseld.