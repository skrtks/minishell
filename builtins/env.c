/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/06 14:08:49 by mmourik       #+#    #+#                 */
/*   Updated: 2020/07/12 11:18:46 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_node		*env(t_node *node, t_env *env_list)
{
	g_exitcode = 0;
	if (node->next != NULL && node->next->command != SEMICOLON)
	{
		err_message("env", node->next->data,
				"No such file or directory");
		g_exitcode = 2;
	}
	else
		while (env_list)
		{
			ft_printf("%s\n", env_list->data);
			env_list = env_list->next;
		}
	while (node && node->type != SYMBOL && node->type != REDIR)
		node = node->next;
	return (node);
}
