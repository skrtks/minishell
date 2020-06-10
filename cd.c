/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/06 13:52:18 by skorteka      #+#    #+#                 */
/*   Updated: 2020/06/10 19:52:32 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"
#include "shell.h"
#include "./libft/libft.h"
#include "errno.h"
#include <unistd.h>
#include <string.h>

static char *get_homedir(t_env *env_list)
{
	char *home_dir;
	t_env *ptr;

	ptr = env_list;
	while (ptr)
	{
		if (!ft_strncmp(ptr->data, "HOME=", 5))
		{
		    home_dir = ft_strdup(ptr->data + 5);
		}
		ptr = ptr->next;
	}
	return (home_dir);
}

t_node *cd(t_node *node, t_env *env_list)
{
	char *path;
	char *home_dir;

	home_dir = get_homedir(env_list);
	if (!home_dir)
    {
    	ft_printf("Error loading home directory, try again.\n");
    	return (NULL);
    }
	if (node->next)
	{
		node = node->next;
		path = node->data;
	}
	else
		path = home_dir;
	if (chdir(path))
	{
		ft_printf("Error: %s\n", strerror(errno));
		errno = 0;
	}
	while (node && node->command != SEMICOLON)
		node = node->next;
	free(home_dir);
	return (node);
}
