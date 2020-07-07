/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/12 12:02:16 by sam           #+#    #+#                 */
/*   Updated: 2020/07/06 17:14:51 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "execute.h"
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "./libft/libft.h"

char		**free_array(char **array)
{
	int i;

	if (!array)
		return (NULL);
	i = 0;
	while (array[i])
	{
		if (array[i])
			free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
	return (NULL);
}

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

static void	do_fork(char *filename, char **argv, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		ft_printf("%s\n", strerror(errno));
		return ;
	}
	if (pid == 0)
	{
		// signal(SIGINT, SIG_DFL);
		// signal(SIGQUIT, SIG_DFL);
		// signal(SIGTSTP, SIG_DFL);
		if (execve(filename, argv, envp))
			ft_printf("bash: %s\n", strerror(errno));
		exit(1);
	}
	else
		wait(&status);
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
		return (NULL);
	}
	do_fork(filename, argv, envp);
	free_array(argv);
	free_array(envp);
	while (node && node->type != SYMBOL && node->type != REDIR)
		node = node->next;
	return (node);
}
