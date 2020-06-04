/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 10:37:24 by samkortekaa   #+#    #+#                 */
/*   Updated: 2020/06/04 13:00:09 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft/libft.h"
#include "lexer.h"

void	free_list(node_t **head_origin)
{
	node_t *head;
	node_t *tmp;

	head = *head_origin;
	while (head != NULL)
	{
		tmp = head->next;
		free(head);
		head = tmp;
	}
	*head_origin = NULL;
}

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
