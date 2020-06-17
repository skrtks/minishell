/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/06 13:25:52 by mmourik       #+#    #+#                 */
/*   Updated: 2020/06/17 12:00:16 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer.h"
#include "../libft/libft.h"

t_node	*pwd(t_node *node)
{
	char	*path;

	path = getcwd(NULL, 0);
	ft_printf("%s\n", path);
	free(path);
	while (node && node->command != SEMICOLON && node->command != PIPE)
		node = node->next;
	return (node);
}
