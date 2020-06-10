/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sam <sam@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/10 15:08:05 by merelmourik   #+#    #+#                 */
/*   Updated: 2020/06/10 15:59:24 by sam           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft/libft.h"
#include "lexer.h"

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

void		add_front(t_node **head, char *str)
{
	t_node *node;

	if (!(node = malloc(sizeof(t_node))))
		exit(1);
	node->next = *head;
	node->data = ft_strdup(str);
	*head = node;
}

int	add_env_node(t_node **head, char *env_var)
{
	t_node *node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (1);
	node->next = NULL;
	node->data = ft_strdup(env_var);
	add_to_back(head, node);
	return (0);
}
