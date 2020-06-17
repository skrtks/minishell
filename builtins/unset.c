/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/11 13:21:54 by skorteka      #+#    #+#                 */
/*   Updated: 2020/06/17 12:00:20 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "lexer.h"
#include "libft/libft.h"

void		remove_node(t_env **node_cur, t_env **node_prev, t_env **head)
{
	if ((*node_prev))
		(*node_prev)->next = (*node_cur)->next;
	else
		*head = (*node_cur)->next;
	free((*node_cur)->data);
	free((*node_cur));
	(*node_cur) = NULL;
}

static int	len_and_check(char *input)
{
	int n;

	n = 0;
	while (input[n])
	{
		if (input[n] == '=')
		{
			ft_printf("unset: `%s': not a valid identifier\n", input);
			return (-1);
		}
		n++;
	}
	return (n + 1);
}

int			compare(const char *input, const char *in_list, int n)
{
	int	i;

	i = 0;
	while (i < n && (input[i] != '\0' || in_list[i] != '\0'))
	{
		if (input[i] != in_list[i] && in_list[i] != '=')
			return (input[i] - in_list[i]);
		if (in_list[i] == '=')
			return (0);
		i++;
	}
	return (0);
}

static void	remove_env_var(char *data, t_env **list)
{
	int		len;
	t_env	*ptr;
	t_env	*previous;

	ptr = *list;
	len = len_and_check(data);
	if (len == -1)
		return ;
	previous = NULL;
	while (ptr)
	{
		if (!compare(data, ptr->data, len))
		{
			remove_node(&ptr, &previous, list);
			break ;
		}
		previous = ptr;
		ptr = ptr->next;
	}
}

t_node		*unset(t_node *node, t_lists **list)
{
	if (node->next)
		node = node->next;
	else
		return (NULL);
	while (node)
	{
		remove_env_var(node->data, &(*list)->export_list);
		remove_env_var(node->data, &(*list)->env_list);
		node = node->next;
	}
	return (node);
}
