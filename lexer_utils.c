/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 10:37:24 by samkortekaa   #+#    #+#                 */
/*   Updated: 2020/06/10 09:56:23 by merelmourik   ########   odam.nl         */
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

void	add_env_node(t_node **head, char *env_var)
{
	t_node *node;

	node = malloc(sizeof(t_node));
	if (!node)
		exit(1);
	node->next = NULL;
	node->data = ft_strdup(env_var);
	add_to_back(head, node);
}
