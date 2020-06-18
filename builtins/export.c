/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/06 15:41:37 by mmourik       #+#    #+#                 */
/*   Updated: 2020/06/18 13:09:42 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft/libft.h"

static int		compare_data(const char *str1, const char *str2)
{
	int i;

	i = 0;
	while (str1[i] || str2[i])
	{
		if (str1[i] <= str2[i])
			return (0);
		if (str1[i] > str2[i])
			return (1);
		i++;
	}
	if (str2[i] == '\0')
		return (1);
	return (0);
}

static void		sort_list(t_env **export_list)
{
	t_env	*ptr;
	t_env	*next;
	int		swap;

	swap = 1;
	while (swap)
	{
		swap = 0;
		ptr = *export_list;
		next = ptr->next;
		while (ptr && ptr->next)
		{
			if (compare_data(ptr->data, next->data))
			{
				ptr->next = next->next;
				next->next = *export_list;
				*export_list = next;
				swap = 1;
			}
			ptr = ptr->next;
			if (ptr)
				next = ptr->next;
		}
	}
}

void			check_existence(char *str, t_env **list)
{
	int		len;
	t_env	*ptr;
	t_env	*previous;

	ptr = *list;
	len = check_equal_sign(str);
	if (len == -1)
		return ;
	previous = NULL;
	while (ptr)
	{
		if (!compare(str, ptr->data, len))
		{
			remove_node(&ptr, &previous, list);
			break ;
		}
		previous = ptr;
		ptr = ptr->next;
	}
}

t_node			*extend_lists(t_node *node, t_lists **list)
{
	char	*temp;
	char	*temp2;
	int		equal_sign;

	temp2 = ft_strdup(node->next->data);
	temp = ft_strdup(node->next->data);
	equal_sign = check_equal_sign(node->next->data);
	while (node->next != NULL && node->next->command != SEMICOLON)
	{
		node = node->next;
		check_existence(node->data, &(*list)->export_list);
		check_existence(node->data, &(*list)->env_list);
		while (node->next != NULL && node->command != SEMICOLON)
		{
			free(temp);
			if (!(temp = ft_strjoin(temp2, node->next->data)))
				return (NULL);
			node = node->next;
		}
		free(temp2);
		add_export_node(&(*list)->export_list, temp);
		if (equal_sign >= 0)
			extend_env_list(temp, &(*list)->env_list);
		free(temp);
	}
	node = node->next;
	return (node);
}

t_node			*export_cmd(t_node *node, t_lists **list)
{
	t_env *head;

	if (node->next != NULL && node->next->command != SEMICOLON)
		return (extend_lists(node, list));
	sort_list(&(*list)->export_list);
	head = (*list)->export_list;
	while ((*list)->export_list)
	{
		ft_printf("declare -x %s\n", (*list)->export_list->data);
		(*list)->export_list = (*list)->export_list->next;
	}
	(*list)->export_list = head;
	node = node->next;
	return (node);
}
