/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/06 14:08:49 by mmourik       #+#    #+#                 */
/*   Updated: 2020/06/17 12:00:02 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_node		*env(t_node *node, t_env *env_list)
{
	while (env_list)
	{
		printf("%s\n", env_list->data);
		env_list = env_list->next;
	}
	node = node->next;
	return (node);
}
