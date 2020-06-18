/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/09 15:21:39 by sam           #+#    #+#                 */
/*   Updated: 2020/06/18 08:10:06 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils/utils.h"

void	exit_shell(t_node *cmd_lst, t_env **env_lst, t_env **exp_lst, int code)
{
	if (env_lst)
		free_envlist(env_lst);
	if (exp_lst)
		free_envlist(exp_lst);
	if (cmd_lst)
		free_cmdlist(&cmd_lst);
	system("leaks minishell"); // Remove before submitting
	exit(code);
}
