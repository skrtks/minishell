/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/17 11:26:48 by merelmourik   #+#    #+#                 */
/*   Updated: 2020/06/17 11:53:44 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char *clean_exit_extract_word(char *s1, char *s2, char *s3)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	if (s3)
		free(s3);
	return (NULL);
}

void	free_envlist(t_env **head_origin)
{
	t_env *head;
	t_env *tmp;

	head = *head_origin;
	while (head != NULL)
	{
		tmp = head->next;
		if (head->data)
			free(head->data);
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
			free(head->data);
		free(head);
		head = tmp;
	}
	*head_origin = NULL;
}
