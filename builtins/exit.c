/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/09 15:21:39 by sam           #+#    #+#                 */
/*   Updated: 2020/07/07 16:56:04 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils/utils.h"

void	exit_shell(t_node *cmd_lst, t_env **env_lst, t_env **exp_lst, int code)
{
	int i;

	ft_printf("exit\n");
	if (cmd_lst && cmd_lst->next)
	{
		i = 0;
		while (cmd_lst->next->data[i])
		{
			if (!ft_isdigit(cmd_lst->next->data[i]))
			{
				ft_printf("minishell: exit: %s: numeric argument required\n",\
				cmd_lst->next->data);
				g_exitcode = 255;
				break ;
			}
			i++;
		}
		code = ft_atoi(cmd_lst->next->data);
	}
	if (env_lst)
		free_envlist(env_lst);
	if (exp_lst)
		free_envlist(exp_lst);
	if (cmd_lst)
		free_cmdlist(&cmd_lst);
	system("leaks minishell"); // Remove before submitting
	exit(code);
}

//255> check