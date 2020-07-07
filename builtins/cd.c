/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/06 13:52:18 by skorteka      #+#    #+#                 */
/*   Updated: 2020/07/07 21:21:24 by merelmourik   ########   odam.nl         */
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

static int	old_pwd(t_lists **list)
{
	char *path;
	char *pwd;

	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		g_exitcode = 2;
		return (-1);
	}
	if (!(pwd = ft_strjoin("OLDPWD=", path)))
	{
		g_exitcode = 12;
		return (-1);
	}
	check_existence_env(pwd, &(*list)->env_list);
	add_env_node(&(*list)->env_list, pwd);
	free(path);
	free(pwd);
	return (0);
}

static int	new_pwd(t_lists **list)
{
	char *path;
	char *pwd;

	if (!(path = getcwd(NULL, 0)))
	{
		g_exitcode = 2;
		return (-1);
	}
	if (!(pwd = ft_strjoin("PWD=", path)))
	{
		g_exitcode = 12;
		return (-1);
	}
	check_existence_env(pwd, &(*list)->env_list);
	add_env_node(&(*list)->env_list, pwd);
	free(path);
	free(pwd);
	return (0);
}

t_node		*cd(t_node *node, t_lists **list)
{
	char *home_dir;
	char *path;

	if (old_pwd(list) == -1)
		return (NULL);
	if (!(home_dir = get_homedir((*list)->env_list)))				//welke error code?
		return (NULL);
	path = home_dir;
	if (node && node->next && node->next->data[0] != '\0')
	{
		node = node->next;
		path = node->data;
	}
	if (chdir(path) == -1)
	{
		ft_printf("minishell: cd: %s: %s\n", node->data, strerror(errno));
		g_exitcode = 1;
		errno = 0;
	}
	else
		g_exitcode = 0;
	if (new_pwd(list) == -1)
	{
		free(home_dir);
		return (NULL);
	}
	while (node && node->type != SYMBOL && node->type != REDIR)
		node = node->next;
	free(home_dir);
	return (node);
}
//pwd komt nu onderaan de env list te staan ipv ergens in het midden