/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/09 20:32:18 by merelmourik   #+#    #+#                 */
/*   Updated: 2020/07/13 16:09:50 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils/utils.h"
#include <signal.h>

static t_lists	*get_env(char **envp)
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

void process_input(t_node **command_list, char **input, t_lists **list)
{
	signal(SIGQUIT, sig_handler);
	signal(SIGINT, sig_handler);
	signal(SIGSTOP, sig_handler);
	if (((*command_list) = lexer((*input), (*list)->env_list)))
		if (!check_cmd_list((*command_list)))
			parse((*command_list), list);
	free((*input));
	(*input) = NULL;
	free_cmdlist(command_list);
}

int				main(__unused int argc, __unused char **argv, char **envp)
{
	char	*input;
	t_node	*command_list;
	t_lists	*list;
	int ret;

	if (!(list = get_env(envp)))
		exit(1);
	while (1)
	{
		write(1, "minishell> $ ", 13);
		set_signal();
		if ((ret = get_next_line(0, &input)) == -1)
			break ;
		else if (ret == 0 && (!input || !input[0]))
			exit_minishell(NULL, &list->env_list, &list->export_list, 0);
		else if (ret != 0)
			process_input(&command_list, &input, &list);
		else
		{
			ft_printf("\n");
			free(input);
			input = NULL;
		}
	}
	return (0);
}
