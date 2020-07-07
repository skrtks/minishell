/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/06 13:25:52 by mmourik       #+#    #+#                 */
/*   Updated: 2020/07/07 21:34:19 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft/libft.h"

t_node	*pwd(t_node *node)
{
	char	*path;

	if (!(path = getcwd(NULL, 0)))
	{
		g_exitcode = 2;
		return (NULL);
	}
	ft_printf("%s\n", path);
	free(path);
	while (node && node->type != SYMBOL && node->type != REDIR)
		node = node->next;
	return (node);
}
