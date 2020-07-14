/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   linkedlist_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/10 15:08:05 by merelmourik   #+#    #+#                 */
/*   Updated: 2020/07/14 13:30:03 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int			add_env_node(t_env **head, char *env_var)
{
	t_env *node;

	node = malloc(sizeof(t_env));
	if (node == NULL)
		return (-1);
	node->next = NULL;
	node->data = ft_strdup(env_var);
	if (node->data == NULL)
		return (-1);
	add_to_back_env(head, node);
	return (0);
}

static char	*export_data(char *str)
{
	int		i;
	char	*new;

	new = malloc(sizeof(char) * (ft_strlen(str) + 3));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		new[i] = str[i];
		i++;
	}
	new[i] = str[i];
	if (str[i] == '\0')
		return (new);
	new[i + 1] = '\"';
	i += 2;
	while (str[i - 1])
	{
		new[i] = str[i - 1];
		i++;
	}
	new[i] = '\"';
	new[i + 1] = '\0';
	return (new);
}

int			add_export_node(t_env **head, char *export_var)
{
	t_env	*node;
	int		check;

	check = 0;
	node = malloc(sizeof(t_env));
	if (node == NULL)
		return (-1);
	if (check_equal_sign(export_var))
	{
		export_var = export_data(export_var);
		if (!export_var)
			return (-1);
		check = 1;
	}
	node->next = NULL;
	node->data = ft_strdup(export_var);
	if (node->data == NULL)
		return (-1);
	if (check == 1)
		free(export_var);
	add_to_back_env(head, node);
	return (0);
}

void		add_to_back_env(t_env **head, t_env *node)
{
	t_env *ptr;

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
