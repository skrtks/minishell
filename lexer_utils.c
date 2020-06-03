/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: samkortekaas <samkortekaas@student.codam.nl> +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 10:37:24 by samkortekaas  #+#    #+#                 */
/*   Updated: 2020/06/03 10:38:40 by samkortekaas  ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft/libft.h"
#include "lexer.h"

void set_info(int command, int type, node_t *node)
{
	node->command = command;
	node->type = type;
}

void	add_to_back(node_t **head, node_t *node)
{
	node_t *ptr;

	if (!(*head))
		(*head) = node;
	else
	{
		ptr = *head;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = node;
	}
}
