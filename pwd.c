/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmourik <mmourik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/06 13:25:52 by mmourik       #+#    #+#                 */
/*   Updated: 2020/06/06 13:57:23 by mmourik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "./libft/libft.h"

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
