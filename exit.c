/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sam <sam@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/09 15:21:39 by sam           #+#    #+#                 */
/*   Updated: 2020/06/11 09:26:44 by sam           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "exit.h"
#include "lexer.h"

void exit_shell(t_node *command_list, t_node **env_list, int exit_code)
{
	if (env_list)
		free_list(env_list);
	if (command_list)
		free_list(&command_list);
	system("leaks minishell"); // Remove before submitting
	exit (exit_code);
}
