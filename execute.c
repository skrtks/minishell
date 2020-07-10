/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/12 12:02:16 by sam           #+#    #+#                 */
/*   Updated: 2020/07/10 13:43:06 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "execute.h"
#include <string.h>
#include "./libft/libft.h"
#include "utils/utils.h"

static char	**list_to_array(t_node *node)
{
	t_node	*head;
	char	**argv;
	int		list_len;

	head = node;
	list_len = 0;
	while (node && node->type != SYMBOL && node->type != REDIR)
	{
		node = node->next;
		list_len++;
	}
	if (!(argv = malloc(sizeof(char *) * (list_len + 1))))
		return (NULL);
	argv[list_len] = NULL;
	node = head;
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
	t_env	*head;
	char	**envp;
	int		list_len;

	head = node;
	list_len = 0;
	while (node)
	{
		node = node->next;
		list_len++;
	}
	if (!(envp = malloc(sizeof(char *) * (list_len + 1))))
		return (NULL);
	envp[list_len] = NULL;
	node = head;
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

	if ((pid = fork()) == -1)
	{
		ft_printf("%s\n", strerror(errno));
		g_exitcode = 10;
		return (-1);
	}
	if (pid == 0)
	{
		if (execve(filename, argv, envp))
			ft_printf("minishell: %s: %s\n", filename, strerror(errno));
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
		free_array(argv);
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
