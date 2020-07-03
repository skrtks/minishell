/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   res_save.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmourik <mmourik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/02 16:31:55 by mmourik       #+#    #+#                 */
/*   Updated: 2020/07/02 16:32:50 by mmourik       ########   odam.nl         */
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

int		arrow_left(t_node *ptr)
{
	int		left;

	left = 0;
	while (ptr && ptr->command != SEMICOLON)
	{
		if (ptr->command == ARROW_LEFT)
			left++;
		ptr = ptr->next;
	}
	return (left);
}

int		arrow_right(t_node *ptr)
{
	int		right;

	right = 0;
	while (ptr && ptr->command != SEMICOLON)
	{
		if (ptr->command == ARROW_RIGHT)
			right++;
		ptr = ptr->next;
	}
	return (right);
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
	int		fd2;
	int		left;
	int		right;
	t_node	*ptr;
	
	ptr = cmd_list;
	left = arrow_left(ptr);
	right = arrow_right(ptr);
	i--;
	if (left > 0)
		while (ptr && ptr->command != SEMICOLON)
		{
			if (ptr->command == ARROW_LEFT)
				left--;
			if (left == 0)
			{
				fd2 = open(ptr->next->data, O_RDWR);		//rdonly
				dup2(fd2, 0);
				break ;
			}
			ptr = ptr->next;
		}
	while (cmd_list && cmd_list->command != SEMICOLON)
	{
		if (cmd_list->command == ARROW_RIGHT)
		{
			right--;
			fd  = open(cmd_list->next->data, O_RDWR | O_CREAT | O_TRUNC, 0644);
		}
		if (cmd_list->command == ARROW_DOUBLE)
		{
			right--;
			fd  = open(cmd_list->next->data, O_RDWR | O_CREAT | O_APPEND, 0644);
		}
			if (right > 0)
				close(fd);
			if (right == 0)
				dup2(fd, 1);
			cmd_list = cmd_list->next;
	}
	//close(fd);
	return ;
}
