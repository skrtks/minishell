/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <skorteka@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 15:03:35 by skorteka      #+#    #+#                 */
/*   Updated: 2020/07/01 15:15:47 by mmourik       ########   odam.nl         */
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
	while (node && node->type != SYMBOL && node->type != REDIRECTION)
	{
		ft_printf("%s ", node->data);
		node = node->next;
	}
	if (!flag)
		ft_printf("\n");
	return (node);
}
