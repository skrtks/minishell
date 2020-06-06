/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <skorteka@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 15:03:35 by skorteka      #+#    #+#                 */
/*   Updated: 2020/06/06 13:22:34 by skorteka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "echo.h"
#include "lexer.h"
#include "shell.h"
#include "./libft/libft.h"

t_node *echo(t_node *ptr)
{
	int flag;

	flag = 0;
	ptr = ptr->next;
	if (ptr && ptr->command == N)
	{
		flag = 1;
		ptr = ptr->next;
	}
	while (ptr && ptr->command != SEMICOLON)
	{
		ft_printf("%s ", ptr->data);
		ptr = ptr->next;
	}
	if (!flag)
		ft_printf("\n");
	return (ptr);
}