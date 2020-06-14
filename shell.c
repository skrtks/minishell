/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/09 11:23:06 by sam           #+#    #+#                 */
/*   Updated: 2020/06/14 16:28:16 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "lexer.h"
#include "parser.h"
#include "./libft/libft.h"

t_lists	*get_env(char **envp)
{
	t_lists	*list;

	if (!(list = malloc(sizeof(t_lists))))
		return (NULL);
	list->env_list = NULL;
	list->export_list = NULL;
	while (*envp)
	{
		if (add_env_node(&list->env_list, *envp))
			return (NULL);
		if (add_export_node(&list->export_list, *envp))
			return (NULL);
		envp++;
	}
	return (list);
}

void	sig_handler()
{
	ft_printf("\nminishell> $ ");
	return ;
}

int		main(int argc, char **argv, char **envp)
{
	int		ret;
	char	*input;
	t_node	*command_list;
	t_lists	*list;

	list = get_env(envp);
	// while (list->env_list)
	// {
	// 	printf("%s\n", list->env_list->data);
	// 	list->env_list = list->env_list->next;
	// }
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	signal(SIGTSTP, sig_handler);
	if (!list)
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
		free(input);
		input = NULL;
		parse(command_list, &list);
		free_cmdlist(&command_list);
	}
	argc = 0;
	argv = NULL;
	//free_envlist(&env_list);			//listst van maken
	return (0);
}
