/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 15:03:35 by skorteka      #+#    #+#                 */
/*   Updated: 2020/07/07 10:13:56 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft/libft.h"

t_node	*echo(t_node *node)
{
	int flag;

	flag = 0;
	node = node->next;
	if (node && node->command == N)
	{
		flag = 1;
		node = node->next;
	}
	while (node && node->type != SYMBOL && node->type != REDIR)
	{
		ft_printf("%s", node->data);
		if (node->next && node->next->type != SYMBOL && \
			node->next->type != REDIR)
			ft_printf(" ");
		node = node->next;
	}
	if (!flag)
		ft_printf("\n");
	return (node);
}
