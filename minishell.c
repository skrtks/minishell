
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/09 11:23:06 by sam           #+#    #+#                 */
/*   Updated: 2020/07/07 11:56:57 by merelmourik   ########   odam.nl         */
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
	char	*input;
	t_node	*command_list;
	t_lists	*list;

	if (!(list = get_env(envp)))
		exit(1);
	// signal(SIGINT, sig_handler);
	// signal(SIGQUIT, sig_handler);
	// signal(SIGTSTP, sig_handler);
	while (1)
	{
		write(1, "minishell> $ ", 13);
		if (get_next_line(0, &input) == -1)
			break ;
		if ((command_list = lexer(input, list->env_list)))
			parse(command_list, &list);
		free(input);
		input = NULL;
		free_cmdlist(&command_list);
	}
	(void) argc;
	(void) argv;
	return (0);
}
