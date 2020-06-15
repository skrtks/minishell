/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: sam <sam@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 14:33:37 by samkortekaa   #+#    #+#                 */
/*   Updated: 2020/06/15 19:15:58 by sam           ########   odam.nl         */
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
#include "./libft/libft.h"
#include <sys/stat.h>

int clean_on_exit(char *path, char *cur_dir, char **paths_arr, int ret_val) {
	chdir(cur_dir);
	if (path)
		free(path);
	if (cur_dir)
		free(cur_dir);
	if (paths_arr)
		free_array(paths_arr);
	return (ret_val);
}

char **get_path_array(t_env *env_list)
{
	char *path;
	char **paths_arr;

	path = NULL;
	while (env_list)
	{
		if (!ft_strncmp("PATH=", env_list->data, 5))
		{
			path = ft_strdup(env_list->data + 5); // Protect?
			break ;
		}
		env_list = env_list->next;
	}
	paths_arr = ft_split(path, ':'); // Protect? (deze heeft geen probleem met NULL input)
	if (path)
		free(path);
	return (paths_arr);
}

int check_for_path(char **cmd, t_env *env_list)
{
	char *path;
	char *cur_dir;
	char **paths_arr;
	struct stat buffer;
	int i;

	paths_arr = get_path_array(env_list); // Won't crash if not protected, still do it?
	cur_dir = getcwd(NULL, 0);
	path = NULL;
	i = 0;
	while (paths_arr && paths_arr[i])
	{
		chdir(paths_arr[i]);
		if (stat(*cmd, &buffer) == 0)
		{
			free(path);
			path = ft_strjoin(paths_arr[i], "/"); // Protect?
			free(paths_arr[i]);
			paths_arr[i] = path;
			path = ft_strjoin(path, *cmd); // Protect?
			free(*cmd);
			*cmd = ft_strdup(path); // Protect?
			return (clean_on_exit(path, cur_dir, paths_arr, 1));
		}
		i++;
	}
	return (clean_on_exit(path, cur_dir, paths_arr, 0));
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
