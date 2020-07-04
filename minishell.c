
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/09 11:23:06 by sam           #+#    #+#                 */
/*   Updated: 2020/07/03 11:27:34 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "parser.h"
#include "utils/utils.h"
#include "expand.h"

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

void	sig_handler(void)
{
	ft_printf("\nminishell> $ ");
}

int		main(int argc, char **argv, char **envp)
{
	int		ret;
	char	*input;
	t_node	*command_list;
	t_lists	*list;

	list = get_env(envp);
	// signal(SIGINT, sig_handler);
	// signal(SIGQUIT, sig_handler);
	// signal(SIGTSTP, sig_handler);
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
		if ((command_list = lexer(input, list->env_list)))
			parse(command_list, &list);
			// if (!expand(command_list, list->env_list))
		free(input);
		input = NULL;
		free_cmdlist(&command_list);
	}
	(void) argc;
	(void) argv;
	return (0);
}
