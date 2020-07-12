/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_path.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/16 09:26:09 by sam           #+#    #+#                 */
/*   Updated: 2020/07/12 11:14:10 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <sys/stat.h>

static int	clean_exit(char *path, char *cur_dir, char **paths_arr, int ret_val)
{
	chdir(cur_dir);
	if (path)
		free(path);
	if (cur_dir)
		free(cur_dir);
	if (paths_arr)
		free_array(paths_arr);
	return (ret_val);
}

static char	**get_path_array(t_env *env_list)
{
	char *path;
	char **paths_arr;

	path = NULL;
	while (env_list)
	{
		if (!ft_strncmp("PATH=", env_list->data, 5))
		{
			path = ft_strdup(env_list->data + 5);
			break ;
		}
		env_list = env_list->next;
	}
	paths_arr = ft_split(path, ':');
	if (path)
		free(path);
	return (paths_arr);
}

static int	construct_path(char *path, char **cmd)
{
	char *tmp;
	char *tmp2;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (0);
	tmp2 = ft_strjoin(tmp, *cmd);
	if (!tmp2)
	{
		free(tmp);
		return (0);
	}
	free(*cmd);
	*cmd = ft_strdup(tmp2);
	free(tmp);
	free(tmp2);
	if (!*cmd)
		return (0);
	else
		return (1);
}

int			check_for_path(char **cmd, t_env *env_list)
{
	char		*path;
	char		*cur_dir;
	char		**paths_arr;
	int			i;
	struct stat	buffer;

	paths_arr = get_path_array(env_list);
	cur_dir = getcwd(NULL, 0);
	path = NULL;
	i = 0;
	while (paths_arr && paths_arr[i])
	{
		chdir(paths_arr[i]);
		if (stat(*cmd, &buffer) == 0)
		{
			if (construct_path(paths_arr[i], cmd))
				return (clean_exit(path, cur_dir, paths_arr, 1));
			else
				return (clean_exit(path, cur_dir, paths_arr, 0));
		}
		i++;
	}
	return (clean_exit(path, cur_dir, paths_arr, 0));
}
