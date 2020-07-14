/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/09 15:21:39 by sam           #+#    #+#                 */
/*   Updated: 2020/07/12 15:05:45 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	invalid_exit(t_node *cmd_lst)
{
	err_message("exit", cmd_lst->next->data,
				"numeric argument required");
	g_exitcode = 255;
}

void		free_lists(t_node *cmd, t_env *env, t_env *exp)
{
	if (env)
		free_envlist(&env);
	if (exp)
		free_envlist(&exp);
	if (cmd)
		free_cmdlist(&cmd);
}

void		exit_minishell(t_node *cmd, t_env **env, t_env **exp, int code)
{
	int i;

	write(2, "exit\n", 5);
	g_exitcode = 0;
	if (cmd && cmd->next)
	{
		code = ft_atoi(cmd->next->data);
		code = (code >= 0 && code <= 255 ? code : 255);
		i = 0;
		while (cmd->next->data[i])
		{
			if (ft_isdigit(cmd->next->data[i]) || (i == 0 && \
			(cmd->next->data[i] == '-' || cmd->next->data[i] == '+')))
				i++;
			else
			{
				invalid_exit(cmd);
				code = 255;
				break ;
			}
		}
	}
	free_lists(cmd, *env, *exp);
	system("leaks minishell"); // Remove before submitting
	exit(code);
}
