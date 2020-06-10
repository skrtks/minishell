/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/09 15:21:39 by sam           #+#    #+#                 */
/*   Updated: 2020/06/10 19:59:23 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "exit.h"
#include "lexer.h"

void exit_shell(t_node *command_list, t_env **env_list, int exit_code)
{
	if (env_list)
		free_envlist(env_list);
	if (command_list)
		free_cmdlist(&command_list);
	system("leaks minishell");
	exit (exit_code);
}
