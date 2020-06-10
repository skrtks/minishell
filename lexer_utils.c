/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 10:37:24 by samkortekaa   #+#    #+#                 */
/*   Updated: 2020/06/10 19:57:37 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft/libft.h"
#include "lexer.h"

void	free_envlist(t_env **head_origin)
{
	t_env *head;
	t_env *tmp;

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

void	free_cmdlist(t_node **head_origin)
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
