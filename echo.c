/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <skorteka@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 15:03:35 by skorteka      #+#    #+#                 */
/*   Updated: 2020/06/05 15:53:18 by skorteka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "echo.h"
#include "lexer.h"
#include "shell.h"
#include "./libft/libft.h"

void echo(t_node *ptr)
{
	ft_printf("Hello from echo %s\n", ptr->data);
}