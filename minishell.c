/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/09 20:32:18 by merelmourik   #+#    #+#                 */
/*   Updated: 2020/07/14 13:39:33 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils/utils.h"

static void		new_line_and_free(char **input)
{
	ft_printf("\n");
	free(*input);
	*input = NULL;
}

static void		process_input(t_node **cmd_list, char **input, t_lists **list)
{
	signal(SIGQUIT, sig_handler);
	signal(SIGINT, sig_handler);
	signal(SIGSTOP, sig_handler);
	*cmd_list = lexer(*input, (*list)->env_list);
	if (*cmd_list == NULL)
	{
		free(*input);
		(*input) = NULL;
		free_cmdlist(cmd_list);
		return ;
	}
	if (!check_cmd_list(*cmd_list))
		parse(*cmd_list, list);
	free(*input);
	*input = NULL;
	free_cmdlist(cmd_list);
}

static t_lists	*get_env(char **envp)
{
	t_lists	*list;

	list = malloc(sizeof(t_lists));
	if (list == NULL)
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

int				main(int argc, char **argv, char **envp)
{
	int		ret;
	char	*input;
	t_node	*command_list;
	t_lists	*list;

	list = get_env(envp);
	if (!list)
		exit(1);
	while (1)
	{
		write(1, "minishell> $ ", 13);
		set_signal();
		ret = get_next_line(0, &input);
		if (ret == -1)
			break ;
		else if (ret == 0 && (!input || !input[0]))
			exit_minishell(NULL, &list->env_list, &list->export_list, 0);
		else if (ret != 0)
			process_input(&command_list, &input, &list);
		else
			new_line_and_free(&input);
	}
	(void)argc;
	(void)argv;
	return (0);
}
