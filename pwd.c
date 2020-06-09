/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sam <sam@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/06 13:25:52 by mmourik       #+#    #+#                 */
/*   Updated: 2020/06/09 11:07:28 by sam           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "./libft/libft.h"

// TODO: make sure pwd works with ';'
t_node	*pwd(t_node *node)
{
	char	*path;

	path = getcwd(NULL, 0);
	ft_printf("%s\n", path);
	free(path);
	while (node && node->command != SEMICOLON)
		node = node->next;
	return (node);
}
