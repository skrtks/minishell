/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/06 15:41:37 by mmourik       #+#    #+#                 */
/*   Updated: 2020/06/10 12:18:23 by merelmourik   ########   odam.nl         */
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

void		add_front(t_node **head, char *str)
{
	t_node *node;

	if (!(node = malloc(sizeof(t_node))))
		exit(1);
	node->next = *head;
	node->data = ft_strdup(str);
	*head = node;
}

void		sort_list(t_node **env_list)
{
	t_node	*ptr = NULL;
	t_node	*temp = NULL;
	char	*data;
	int		swap;
	
	if (env_list == NULL)
		return ;
	swap = 1;
	while(swap) 
	{
		swap = 0;
		ptr = *env_list;
		while (ptr->next != NULL)
		{
			temp = ptr->next;
			if (compare_data(ptr->data, temp->data))
			{
				data = ft_strdup(temp->data);
				ptr->next = temp->next;
				temp->next = NULL;
				add_front(env_list, data);
				free (data);
				swap = 1;
			}
			ptr = temp;
		}
	}
	return ;
}

t_node		*export(t_node *node, t_node *env_list)
{
	if (node->next != NULL && node->next->command == OTHER)
	{
		add_env_node(&env_list, node->next->data);
		node = node->next;			//verder over skippen
		return (node);
	}
	sort_list(&env_list);
	while(env_list)
	{
		ft_printf("declare -x %s\n", env_list->data);
		env_list = env_list->next;
	}
	node = node->next;
	return (node);
}
