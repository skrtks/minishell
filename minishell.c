#include <limits.h>
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

void			sig_handler_inp(int _)
{
	(void)_;
	ft_printf("\nminishell> $ ");
	return ;
}

void			sig_handler(int _)
{
	(void)_;
	ft_printf("\n");
	return ;
}

int				main(__unused int argc, __unused char **argv, char **envp)
{
	char	*input;
	t_node	*command_list;
	t_lists	*list;
	int ret;

	signal(SIGQUIT, SIG_IGN); /* ignore ctrl-\ */ //
	if (!(list = get_env(envp)))
		exit(1);
	while (1)
	{
		write(1, "minishell> $ ", 13);
		signal(SIGINT, sig_handler_inp); // ignore ctr-c en print nieuwe cmd promt
		signal(SIGSTOP, sig_handler_inp); // ignore ctr-d en print nieuwe cmd promt
		ret = get_next_line(0, &input);
		if (ret == -1)
			break ;
		else if (ret == 0 && (!input || !input[0])) // Als input leeg is exit minishell
			exit_minishell(NULL, &list->env_list, &list->export_list, 0);
		signal(SIGINT, sig_handler); // ignore ctr-c en print alleen nieuwe regel, geen promt
		signal(SIGSTOP, sig_handler); // ignore ctr-d en print alleen nieuwe regel, geen promt
		if ((command_list = lexer(input, list->env_list)))
			if (!check_cmd_list(command_list))
				parse(command_list, &list);
		free(input);
		input = NULL;
		free_cmdlist(&command_list);
	}
	return (0);
}
