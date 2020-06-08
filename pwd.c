/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sam <sam@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/06 13:25:52 by mmourik       #+#    #+#                 */
/*   Updated: 2020/06/08 22:35:42 by sam           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "./libft/libft.h"

// TODO: make sure pwd works with ';'
t_node	*pwd(t_node *node)
{
	char	*path;

	node = node->next;
	path = getcwd(NULL, 0);
	if (node == NULL || node->command == OTHER)
		ft_printf("%s\n", path);
	free(path);
	return (node);
}
