/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: sam <sam@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 14:33:37 by samkortekaa   #+#    #+#                 */
/*   Updated: 2020/06/15 15:53:56 by sam           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "echo.h"
#include "execute.h"
#include "shell.h"
#include "exit.h"
#include <string.h>
#include "cd.h"
#include "cd.h"
#include "./libft/libft.h"
#include <sys/stat.h>

int check_for_path(char **cmd, t_env *env_list)
{
	char *path;
	char *homedir;
	char **paths_arr;
    struct stat buffer;
    t_env *ptr;
	int i;

    (void)cmd;
    path = NULL;
	ptr = env_list;
	while (ptr)
	{
		if (!ft_strncmp("PATH=", ptr->data, 5))
		{
			path = ft_strdup(ptr->data + 5);
			break ;
		}
		ptr = ptr->next;
	}
    paths_arr = ft_split(path, ':');
    homedir = get_homedir(env_list);
	i = 0;
	while (paths_arr[i])
    {
    	if (chdir(paths_arr[i]))
		{
			ft_printf("Error: %s\n", strerror(errno));
			errno = 0;
		}
        if (stat(*cmd, &buffer) == 0) {
            free(path);
        	path = ft_strjoin(paths_arr[i], "/");
        	free(paths_arr[i]);
        	paths_arr[i] = path;
        	path = ft_strjoin(path, *cmd);
        	free(*cmd);
        	*cmd = path;
            if (chdir(homedir))
			{
				ft_printf("Error: %s\n", strerror(errno));
				errno = 0;
			}
			free(homedir);
			free_array(paths_arr);
            return (1);
        }
        i++;
    }
    if (chdir(homedir))
	{
		ft_printf("Error: %s\n", strerror(errno));
		errno = 0;
	}
	free (path);
	free_array(paths_arr);
	free(homedir);
	return (0);
}

t_node	*execute_cmd(t_node *node, t_lists **list)
{
	if (node->command == ECHO)
		node = echo(node);
	else if (node->command == CD)
		node = cd(node, (*list)->env_list);
	else if (node->command == PWD)
		node = pwd(node);
	else if (node->command == EXPORT)
		node = export_cmd(node, &(*list)->export_list);
	else if (node->command == UNSET)
	{
		node = node->next;
		write(1, "Executed unset\n", 15);
	}
	else if (node->command == ENV)
		node = env(node, (*list)->env_list);
	else if (node->command == EXECUTABLE)
		node = execute(node, (*list)->env_list);
	else if (node->command == EXIT)
		exit_shell(node, &(*list)->env_list, 0);
	else
	{
		if (check_for_path(&(node)->data, (*list)->env_list))
			node = execute(node, (*list)->env_list);
		else
		{
			node = node->next; // Skip to end or next semicolon
			write(1, "Command not recognized\n", 23);
		}
	}
	return (node);
}

void	parse(t_node *cmd_list, t_lists **list)
{
	t_node *ptr;

	ptr = cmd_list;
	while (ptr)
	{
		ptr = execute_cmd(ptr, list);
		if (ptr && ptr->command == SEMICOLON)
			ptr = ptr->next;
	}
}
