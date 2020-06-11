/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/06 15:41:37 by mmourik       #+#    #+#                 */
/*   Updated: 2020/06/11 18:35:24 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "lexer.h"

static int		compare_data(char *str1, char *str2)
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
	return ;
}

void			extend_env_list(char *str, t_env **env_list)
{
	int		i;
	char	*temp;

	i = ft_strlen(str);
	if (!(temp = malloc(sizeof(char) * (i + 1))))
		return ;			//error
	i = 0;
	while (str[i] != ' ' && str[i])
	{
		temp[i] = str[i];
		i++;
	}
	temp[i] = '\0';
	add_env_node(env_list, temp);
	return ;
}

t_node			*export_cmd(t_node *node, t_env **export_list, t_env **env_list)
{
	t_env *head;

	if (node->next != NULL && node->next->command != SEMICOLON)
	{
		while (node->next != NULL && node->next->command != SEMICOLON)
		{
			add_export_node(export_list, node->next->data);
			if (check_equal_sign(node->next->data))
				extend_env_list(node->next->data, env_list);
			node = node->next;
		}
		node = node->next;
		return (node);
	}
	sort_list(export_list);
	head = *export_list;
	while ((*export_list))
	{
		ft_printf("declare -x %s\n", (*export_list)->data);
		(*export_list) = (*export_list)->next;
	}
	*export_list = head;
	node = node->next;
	return (node);
}

//dubbele overschrijven?
//bij export doen