/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/19 13:15:53 by merelmourik   #+#    #+#                 */
/*   Updated: 2020/06/19 16:08:51 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#define _POSIX_SOURCE
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#undef _POSIX_SOURCE
#include <stdio.h>

#include <fcntl.h>
#include "libft/libft.h"
#include <stdio.h>
#include <string.h>
				
void	redirection(t_node *cmd_list)
{
	int		fd;		//write

	fd = 0;
	while (cmd_list && cmd_list->command != SEMICOLON)
	{
		if (cmd_list->command == ARROW_RIGHT)
		{
			fd = open(cmd_list->next->data, O_RDONLY | O_CREAT | O_TRUNC);
			if (fd == -1)
			{
				ft_printf("Error: %s\n", strerror(errno));
				errno = 0;
			}
			break ;
		}
		cmd_list = cmd_list->next;
	}
	dup2(1, fd);
	close(fd);			//nodig?
}

			// if ((dir = opendir(".")) == NULL)
			// 	perror("opendir() error");
			// else
			// {
			// 	while ((entry = readdir(dir)) != NULL)
			// 	{
			// 		if (ft_strcmp(entry->d_name, cmd_list->next->data) == 0)
			// 		{
			// 			printf("het bestand bestaat al\n");
			// 			new_file = 1;
			// 			break ;
			// 		}
			// 	}
			// 	closedir(dir);
			// }