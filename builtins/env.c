/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sam <sam@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/06 14:08:49 by mmourik       #+#    #+#                 */
/*   Updated: 2020/06/18 16:54:43 by sam           ########   odam.nl         */
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
	while (node && node->command != SEMICOLON && node->command != PIPE) 
	{
		node = node->next;
	}
	return (node);
}
