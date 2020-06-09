/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/06 15:41:37 by mmourik       #+#    #+#                 */
/*   Updated: 2020/06/09 12:14:40 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "lexer.h"

t_node		*export(t_node *node, t_node *env_list)
{
	ft_printf("%s\n", node->data);
	while(env_list)
	{
		ft_printf("%s\n", env_list->data);
		env_list = env_list->next;
	}
	node = node->next;
	return (node);
}
