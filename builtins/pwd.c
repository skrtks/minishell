/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/06 13:25:52 by mmourik       #+#    #+#                 */
/*   Updated: 2020/07/12 11:19:05 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_node	*pwd(t_node *node)
{
	char	*path;

	g_exitcode = 0;
	if (!(path = getcwd(NULL, 0)))
	{
		g_exitcode = 2;
		while (node && node->type != SYMBOL && node->type != REDIR)
			node = node->next;
		return (node);
	}
	ft_printf("%s\n", path);
	free(path);
	while (node && node->type != SYMBOL && node->type != REDIR)
		node = node->next;
	return (node);
}
