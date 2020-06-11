/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sam <sam@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/09 15:21:39 by sam           #+#    #+#                 */
/*   Updated: 2020/06/11 09:43:07 by sam           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "exit.h"
#include "lexer.h"

void	exit_shell(t_node *command_list, t_env **env_list, int exit_code)
{
	if (env_list)
		free_envlist(env_list);
	if (command_list)
		free_cmdlist(&command_list);
	system("leaks minishell"); // Remove before submitting
	exit (exit_code);
}
