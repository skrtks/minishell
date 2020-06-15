/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sam <sam@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/12 12:02:16 by sam           #+#    #+#                 */
/*   Updated: 2020/06/15 19:13:23 by sam           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "execute.h"
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "./libft/libft.h"

char **free_array(char **array)
{
	int i;

	if (!array)
		return (NULL);
	i = 0;
	while (array[i])
	{
		if (array[i])
			free (array[i]);
		array[i] = NULL;
		i++;
	}
	free (array);
	array = NULL;
	return (NULL);
}

char **list_to_array(t_node **node)
{
	t_node *head;
	char **argv;
	int list_len;

	head = *node; // Save start pos
	list_len = 0;
	while (*node && (*node)->command != SEMICOLON)
	{
		*node = (*node)->next;
		list_len++;
	}
	argv = malloc(sizeof(char *) * (list_len + 1));
	if (!argv)
		return (NULL);
	argv[list_len] = NULL; // Terminate argv
	*node = head; // Reset start
	list_len = 0;
	while (*node && (*node)->command != SEMICOLON)
	{
		argv[list_len] = ft_strdup((*node)->data);
		if (!argv[list_len])
			return (free_array(argv));
		list_len++;
		*node = (*node)->next;
	}
	return (argv);
}

char **env_list_to_array(t_env **node)
{
	t_env *head;
	char **envp;
	int list_len;
	int i;

	head = *node; // Save start pos
	list_len = 0;
	while (*node)
	{
		*node = (*node)->next;
		list_len++;
	}
	envp = malloc(sizeof(char *) * (list_len + 1));
	if (!envp)
		return (NULL);
	envp[list_len] = NULL; // Terminate envp
	*node = head; // Reset start
	i = 0;
	while (*node)
	{
		envp[i] = ft_strdup((*node)->data);
		if (!envp[i])
			return (free_array(envp));
		i++;
		*node = (*node)->next;
	}
	return (envp);
}

t_node *execute(t_node *node, t_env *env_list)
{
	pid_t pid;
	char *filename;
	char **argv;
	char **envp;
	int status;

	filename = node->data;
	argv = list_to_array(&node);
	envp = env_list_to_array(&env_list);
	if (!argv || !envp)
	{
		free_array(argv);
    	free_array(envp);
		return (NULL);
	}
	pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
    {
    	signal(SIGINT, SIG_DFL); // Kan denk ik weg
    	signal(SIGQUIT, SIG_DFL);
		signal(SIGTSTP, SIG_DFL);
    	
    	if (execve(filename, argv, envp))
    		ft_printf("bash: %s\n", strerror(errno));
    	exit(1);
    }
    else
    {
    	if (wait(&status) == -1) 
    	{
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
    }
    free_array(argv);
    free_array(envp);
	if (node)
		node = node->next;
	return (node);
}