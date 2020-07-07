/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/06 14:08:49 by mmourik       #+#    #+#                 */
/*   Updated: 2020/07/07 21:22:47 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft/libft.h"

t_node		*env(t_node *node, t_env *env_list)
{
	if (node->next != NULL && node->next->command != SEMICOLON)
	{
		ft_printf("env: %s: No such file or directory\n", node->next->data);
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
