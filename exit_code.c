/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_code.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/06 15:24:02 by merelmourik   #+#    #+#                 */
/*   Updated: 2020/07/10 12:35:26 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft/libft.h"

t_node		*exit_code(t_node *node)
{
	ft_printf("%d\n", g_exitcode);
	while (node && node->type != SYMBOL && node->type != REDIR)
		node = node->next;
	return (node);
}
