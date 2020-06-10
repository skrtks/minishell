/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: sam <sam@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/06 15:41:37 by mmourik       #+#    #+#                 */
/*   Updated: 2020/06/10 14:55:00 by sam           ########   odam.nl         */
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
	t_node *ptr;
	t_node *next;
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

void	badd_to_back(t_node **head, t_node *node)
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

void	badd_env_node(t_node **head, char *env_var)
{
	t_node *node;

	node = malloc(sizeof(t_node));
	if (!node)
		exit(1);
	node->next = NULL;
	node->data = ft_strdup(env_var);
	badd_to_back(head, node);
}

t_node		*export(t_node *node, t_node **env_list)
{
	if (node->next != NULL)
	{
		badd_env_node(env_list, node->next->data);
		node = node->next->next;			//verder over skippen
		return (node);
	}
	sort_list(env_list);
	t_node *head;
	
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
