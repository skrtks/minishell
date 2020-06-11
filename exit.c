/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/09 15:21:39 by sam           #+#    #+#                 */
/*   Updated: 2020/06/11 18:16:30 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "exit.h"
#include "lexer.h"

void	exit_shell(t_node *command_list, t_env **env_list, t_env **export_list, int exit_code)
{
	if (env_list)
		free_envlist(env_list);
	if (export_list)
		free_envlist(export_list);
	if (command_list)
		free_cmdlist(&command_list);
	system("leaks minishell"); // Remove before submitting
	exit (exit_code);
}
