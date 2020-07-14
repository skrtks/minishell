/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/12 12:02:16 by sam           #+#    #+#                 */
/*   Updated: 2020/07/14 13:22:09 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <string.h>
#include <errno.h>

static int	linked_list_len(t_node *node, t_env *env)
{
	int list_len;

	list_len = 0;
	if (node)
		while (node && node->type != SYMBOL && node->type != REDIR)
		{
			node = node->next;
			list_len++;
		}
	else if (env)
		while (env)
		{
			env = env->next;
			list_len++;
		}
	return (list_len);
}

static char	**list_to_array(t_node *node)
{
	char	**argv;
	int		list_len;

	list_len = linked_list_len(node, NULL);
	argv = malloc(sizeof(char *) * (list_len + 1));
	if (argv == NULL)
		return (NULL);
	argv[list_len] = NULL;
	list_len = 0;
	while (node && node->type != SYMBOL && node->type != REDIR)
	{
		argv[list_len] = ft_strdup(node->data);
		if (!argv[list_len])
			return (free_array(argv));
		list_len++;
		node = node->next;
	}
	return (argv);
}

static char	**env_list_to_array(t_env *node)
{
	char	**envp;
	int		list_len;

	list_len = linked_list_len(NULL, node);
	envp = malloc(sizeof(char *) * (list_len + 1));
	if (envp == NULL)
		return (NULL);
	envp[list_len] = NULL;
	list_len = 0;
	while (node)
	{
		envp[list_len] = ft_strdup(node->data);
		if (!envp[list_len])
			return (free_array(envp));
		list_len++;
		node = node->next;
	}
	return (envp);
}

static int	do_fork(char *filename, char **argv, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		err_message(NULL, NULL, strerror(errno));
		g_exitcode = 10;
		return (-1);
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTSTP, SIG_DFL);
		if (execve(filename, argv, envp))
			err_message(NULL, NULL, strerror(errno));
		exit(127);
	}
	else
		wait(&status);
	if (WIFEXITED(status))
		g_exitcode = WEXITSTATUS(status);
	return (0);
}

t_node		*execute(t_node *node, t_env *env_list)
{
	char *filename;
	char **argv;
	char **envp;

	filename = node->data;
	argv = list_to_array(node);
	envp = env_list_to_array(env_list);
	if (!argv || !envp)
	{
		if (argv)
			free_array(argv);
		if (envp)
			free_array(envp);
		g_exitcode = 12;
		return (NULL);
	}
	if (do_fork(filename, argv, envp) == -1)
		return (NULL);
	free_array(argv);
	free_array(envp);
	while (node && node->type != SYMBOL && node->type != REDIR)
		node = node->next;
	return (node);
}
