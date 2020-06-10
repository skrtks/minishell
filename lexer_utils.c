/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sam <sam@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 10:37:24 by samkortekaa   #+#    #+#                 */
/*   Updated: 2020/06/10 11:31:29 by sam           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft/libft.h"
#include "lexer.h"

void	free_list(t_node **head_origin)
{
	t_node *head;
	t_node *tmp;

	head = *head_origin;
	while (head != NULL)
	{
		tmp = head->next;
		if (head->data)
			free (head->data);
		free(head);
		head = tmp;
	}
	*head_origin = NULL;
}

void	set_info(int command, int type, t_node *node)
{
	node->command = command;
	node->type = type;
}

void	add_to_back(t_node **head, t_node *node)
{
	t_node *ptr;

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
