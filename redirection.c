/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <skorteka@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 13:15:53 by merelmourik   #+#    #+#                 */
/*   Updated: 2020/07/02 15:18:56 by mmourik       ########   odam.nl         */
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
	return (0);			//error van maken
}

void	fd_error(void)
{
	ft_printf("Error: %s\n", strerror(errno));
	errno = 0;
}

int		arrow_left(t_node *ptr)
{
	int		left;

	left = 0;
	while (ptr && ptr->command != SEMICOLON)
	{
		if (ptr->type == REDIRECTION)
			left++;
		if (ptr->command == ARROW_LEFT)
			break ;
		ptr = ptr->next;
	}
	return (left);
}

void	handle_arrow_left(char *file, int fd)
{
	int		fd2;

	if (!(fd2 = open(file, O_RDWR)))
		fd_error();
	dup2(fd2, 0);
	dup2(fd, 1);
	return ;
}

void	redirection(t_node *cmd_list, int i)
{
	int		fd;
	int		left;

	left = arrow_left(cmd_list);
	while (cmd_list && cmd_list->command != SEMICOLON)
	{
		if (cmd_list->type == REDIRECTION)
		{
			i--;
			if (cmd_list->command == ARROW_LEFT)
			{
				handle_arrow_left(cmd_list->next->data, fd);
				break ;
			}
			if (!(fd = open_file(cmd_list)))
				fd_error();
			if (i > 0 && (left > 0 && i != 1))
				close(fd);
			if (i == 0)
				dup2(fd, 1);
		}
		cmd_list = cmd_list->next;
	}
	close(fd);
	return ;
}
