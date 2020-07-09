/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_code.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/06 15:24:02 by merelmourik   #+#    #+#                 */
/*   Updated: 2020/07/09 20:29:28 by merelmourik   ########   odam.nl         */
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

// 	1 - Catchall for general errors
// 2 - Misuse of shell builtins (according to Bash documentation)
// 126 - Command invoked cannot execute
// 127 - “command not found”
// 128 - Invalid argument to exit
// 128+n - Fatal error signal “n”
// 130 - Script terminated by Control-C
// 255\* - Exit status out of range