/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/06 13:52:18 by skorteka      #+#    #+#                 */
/*   Updated: 2020/07/07 15:43:28 by merelmourik   ########   odam.nl         */
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

static char	*old_pwd(t_lists **list)
{
	char *path;
	char *pwd;

	if (!(path = getcwd(NULL, 0)))
		g_exitcode = 2;
	if (!(pwd = ft_strjoin("OLDPWD=", path)))
		return (NULL);
	check_existence_env(pwd, &(*list)->env_list);
	add_env_node(&(*list)->env_list, pwd);
	free(path);
	free(pwd);
	return (EXIT_SUCCESS);
}

static char	*new_pwd(t_lists **list)
{
	char *path;
	char *pwd;

	path = getcwd(NULL, 0);
	if (path == NULL)
		g_exitcode = 2;
	pwd = ft_strjoin("PWD=", path);
	if (pwd == NULL)
		return (NULL);
	check_existence_env(pwd, &(*list)->env_list);
	add_env_node(&(*list)->env_list, pwd);
	free(path);
	free(pwd);
	return (EXIT_SUCCESS);
}

t_node		*cd(t_node *node, t_lists **list)
{
	char *path;
	char *home_dir;

	old_pwd(list);
	if (!(home_dir = get_homedir((*list)->env_list)))				//welke error code?
	{
		ft_printf("Error loading home directory, try again.\n");
		return (NULL);
	}
	path = home_dir;
	if (node && node->next && node->next->data[0] != '\0')
	{
		node = node->next;
		path = node->data;
	}
	if (chdir(path))
	{
		ft_printf("minishell: cd: %s: %s\n", node->data, strerror(errno));
		g_exitcode = 2;
		errno = 0;
	}
	new_pwd(list);
	while (node && node->type != SYMBOL && node->type != REDIR)
		node = node->next;
	free(home_dir);
	return (node);
}
//pwd komt nu onderaan de env list te staan ipv ergens in het midden