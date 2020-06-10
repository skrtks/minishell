/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sam <sam@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/09 11:23:06 by sam           #+#    #+#                 */
/*   Updated: 2020/06/10 15:49:49 by sam           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <signal.h>
#include "lexer.h"
#include "parser.h"

int	add_env_node(t_node **head, char *env_var)
{
	t_node *node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (1);
	node->next = NULL;
	node->data = ft_strdup(env_var);
	if (!node->data)
		return (1);
	add_to_back(head, node);
	return (0);
}

t_node *get_env(char **envp)
{
	t_node	*head;

	head = NULL;
	while (*envp)
	{
		if (add_env_node(&head, *envp))
			return (NULL);
		envp++;
	}
	return (head);
}

void sig_handler()
{
	ft_printf("\nminishell> $ ");
	return ;
}


int	main(int argc, char **argv, char **envp)
{
	int		ret;
	char	*input;
	t_node	*command_list;
	t_node	*env_list;

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	signal(SIGTSTP, sig_handler);
	env_list = get_env(envp);
	if (!env_list)
	{
		printf("Error starting, env could not be loaded. \nTerminating...\n");
		exit(1);
	}
	while (1)
	{
		write(1, "minishell> $ ", 13);
		ret = get_next_line(0, &input);
		if (ret == -1)
		{
			errno = 0;
			break ;
		}
		command_list = lexer(input);
		free (input);
		parse(command_list, env_list);
		free_list(&command_list);
	}
	argc = 0;
	argv = NULL;
	free_list(&env_list);
	return (0);
}
