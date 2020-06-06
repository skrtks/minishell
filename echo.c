/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <skorteka@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 15:03:35 by skorteka      #+#    #+#                 */
/*   Updated: 2020/06/06 13:29:18 by skorteka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "echo.h"
#include "lexer.h"
#include "shell.h"
#include "./libft/libft.h"

t_node *echo(t_node *node)
{
	int flag;

	flag = 0;
	node = node->next;
	if (node && node->command == N)
	{
		flag = 1;
		node = node->next;
	}
	while (node && node->command != SEMICOLON)
	{
		ft_printf("%s ", node->data);
		node = node->next;
	}
	if (!flag)
		ft_printf("\n");
	return (node);
}