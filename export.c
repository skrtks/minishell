/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: sam <sam@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/06 15:41:37 by mmourik       #+#    #+#                 */
/*   Updated: 2020/06/10 15:44:26 by sam           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "lexer.h"

int			compare_data(char *str1, char *str2)
{
	int i;
	
	i = 0;
	while (str1[i] || str2[i])
	{
		if (str1[i] <= str2[i])
			return(0);
		if (str1[i] > str2[i])
			return(1);
		i++;	
	}
	if (str2[i] == '\0')
		return(1);
	return (0);
}

void		sort_list(t_node **env_list)
{
	t_node	*ptr;
	t_node	*next;
	int		swap;

	swap = 1;
	while (swap)
	{
		swap = 0;
		ptr = *env_list;
		next = ptr->next;
		while (ptr && ptr->next)
		{
			if (compare_data(ptr->data, next->data))
			{
				ptr->next = next->next;
				next->next = *env_list;
				*env_list = next;
				swap = 1;
			}
			ptr = ptr->next;
			if (ptr)
				next = ptr->next;
		}
	}
	return ;
}

t_node		*export(t_node *node, t_node **env_list)
{
	t_node *head;
	
	if (node->next != NULL)
	{
		add_env_node(env_list, node->next->data);
		node = node->next->next;
		return (node);
	}
	sort_list(env_list);
	head = *env_list;
	while((*env_list))
	{
		ft_printf("declare -x %s\n", (*env_list)->data);
		(*env_list) = (*env_list)->next;
	}
	*env_list = head;
	node = node->next;
	return (node);
}
