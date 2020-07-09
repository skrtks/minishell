/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/09 15:21:39 by sam           #+#    #+#                 */
/*   Updated: 2020/07/08 12:02:00 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils/utils.h"

static void	invalid_exit(t_node *cmd_lst)
{
	ft_printf("minishell: exit: %s: numeric argument required\n",\
	cmd_lst->next->data);
	g_exitcode = 255;
}

void free_lists(t_node *cmd, t_env *env, t_env *exp)
{
	if (env)
		free_envlist(&env);
	if (exp)
		free_envlist(&exp);
	if (cmd)
		free_cmdlist(&cmd);
}

void		exit_shell(t_node *cmd, t_env **env, t_env **exp, int code)
{
	int i;

	ft_printf("exit\n");
	if (cmd && cmd->next)
	{
		i = 0;
		while (cmd->next->data[i])
		{
			g_exitcode = 0;
			if (!ft_isdigit(cmd->next->data[i]))
			{
				invalid_exit(cmd);
				break ;
			}
			i++;
		}
		code = ft_atoi(cmd->next->data);
		code = (code >= 0 && code <= 255 ? code : 255);
	}
	free_lists(cmd, *env, *exp);
	system("leaks minishell"); // Remove before submitting
	exit(code);
}