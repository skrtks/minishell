/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <skorteka@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/29 11:46:04 by merelmourik   #+#    #+#                 */
/*   Updated: 2020/06/08 22:24:43 by skorteka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "lexer.h"
#include "parser.h"

void	add_env_node(t_node **head, char *env_var)
{
	t_node *node;

	node = malloc(sizeof(t_node));
	if (!node)
		exit(1);
	node->next = NULL;
	node->data = env_var;
	add_to_back(head, node);
}

t_node *get_env(char **envp)
{
	t_node	*head;

	head = NULL;
	while (*envp)
	{
		add_env_node(&head, *envp);
		envp++;
	}
	return (head);
}

int	main(int argc, char **argv, char **envp)
{
	int		ret;
	char	*input;
	t_node	*command_list;
	t_node	*env_list;

	env_list = get_env(envp);
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
		parse(command_list, env_list);
		free_list(&command_list);
	}
	argc = 0;
	argv = NULL;
	return (0);
}
