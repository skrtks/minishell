/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <skorteka@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/06 13:52:18 by skorteka      #+#    #+#                 */
/*   Updated: 2020/07/04 12:12:24 by skorteka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft/libft.h"
#include "errno.h"
#include <unistd.h>
#include <string.h>

static char	*get_homedir(t_env *env_list)
{
	char	*home_dir;
	t_env	*ptr;

	ptr = env_list;
	while (ptr)
	{
		if (!ft_strncmp(ptr->data, "HOME=", 5))
			home_dir = ft_strdup(ptr->data + 5);
		ptr = ptr->next;
	}
	return (home_dir);
}

static void	old_pwd(t_lists **list)
{
	char *path;
	char *pwd;

	path = getcwd(NULL, 0);
	pwd = ft_strjoin("OLDPWD=", path);
	check_existence_env(pwd, &(*list)->env_list);
	add_env_node(&(*list)->env_list, pwd);
	free(path);
	free(pwd);
	return ;
}

static void	new_pwd(t_lists **list)
{
	char *path;
	char *pwd;

	path = getcwd(NULL, 0);
	pwd = ft_strjoin("PWD=", path);
	check_existence_env(pwd, &(*list)->env_list);
	add_env_node(&(*list)->env_list, pwd);
	free(path);
	free(pwd);
	return ;
}

t_node		*cd(t_node *node, t_lists **list)
{
	char *path;
	char *home_dir;

	old_pwd(list);
	if (!(home_dir = get_homedir((*list)->env_list)))
	{
		ft_printf("Error loading home directory, try again.\n");
		return (NULL);
	}
	path = home_dir;		//niet dup voor gebruiken?
	if (node && node->next && node->next->data[0] != '\0')
	{
		node = node->next;
		path = node->data;
	}
	if (chdir(path))
	{
		ft_printf("minishell: cd: %s: %s\n", node->data, strerror(errno));
		errno = 0;
	}
	new_pwd(list);
	while (node && node->type != SYMBOL && node->type != REDIR)
		node = node->next;
	free(home_dir);
	return (node);
}
