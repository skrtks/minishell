/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <skorteka@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/06 13:52:18 by skorteka      #+#    #+#                 */
/*   Updated: 2020/06/06 16:01:41 by skorteka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"
#include "shell.h"
#include "./libft/libft.h"
#include "errno.h"
#include <unistd.h>
#include <string.h>

void	pwd_command(void) // Weghalen
{
	char	*path;

	path = getcwd(NULL, 0);
	ft_printf("%s\n", path);
	free(path);
}

t_node *cd(t_node *node)
{
	char *path;

	if (node->next)
	{
		node = node->next;
		path = node->data;
	}
	else
		path = "";
	if (chdir(path))
	{
		ft_printf("Error: %s\n", strerror(errno));
		errno = 0;
	}
	pwd_command();
	while (node && node->command != SEMICOLON)
		node = node->next;
	return (node);
}