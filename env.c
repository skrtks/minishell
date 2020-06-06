/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <skorteka@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/06 14:08:49 by mmourik       #+#    #+#                 */
/*   Updated: 2020/06/06 16:34:28 by skorteka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "lexer.h"

t_node		*env(t_node *node, t_node *env_list)
{
	node = node->next;
	while (env_list)
	{
		printf("%s\n", env_list->data);
		env_list = env_list->next;
	}
	return (node);
}
