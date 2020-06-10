/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/06 15:41:37 by mmourik       #+#    #+#                 */
/*   Updated: 2020/06/10 13:01:11 by merelmourik   ########   odam.nl         */
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
				temp->next = NULL;			//dubbele check
				add_front(env_list, data);
				free (data);
				swap = 1;
			}
			ptr = temp;
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
//dubbele pointer verwerken
t_node		*export(t_node *node, t_node *env_list)
{
	t_node *next;

	next = node->next;
	if (next != NULL)
	{
		// while(env_list->next != NULL)
		// {
		// 	ft_printf("declare -x %s\n", env_list->data);
		// 	env_list = env_list->next;
		// }
		badd_env_node(&env_list, next->data);
		node = next->next;			//verder over skippen
		return (node);
	}
	sort_list(&env_list);
	t_node *head;
	
	head = env_list;
	while(env_list->next != NULL)
	{
		ft_printf("declare -x %s\n", env_list->data);
		env_list = env_list->next;
	}
	env_list = head;
	node = next;
	return (node);
}
