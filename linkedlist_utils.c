/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   linkedlist_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/10 15:08:05 by merelmourik   #+#    #+#                 */
/*   Updated: 2020/06/14 15:50:29 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft/libft.h"
#include "lexer.h"

int		add_env_node(t_env **head, char *env_var)
{
	t_env *node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (1);
	node->next = NULL;
	node->data = ft_strdup(env_var);
	add_to_back_env(head, node);
	return (0);
}

char	*export_data(char *str)
{
	int		i;
	char	*new;

	i = ft_strlen(str);
	if (!(new = malloc(sizeof(char) * (i + 3))))
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		new[i] = str[i];
		i++;
	}
	new[i] = str[i];
	new[i + 1] = '\"';
	i += 2;
	while (str[i - 1] && str[i - 1] != ' ')
	{
		new[i] = str[i - 1];
		i++;
	}
	new[i] = '\"';
	new[i + 1] = '\0';
	return (new);
}

int		add_export_node(t_env **head, char *export_var)
{
	t_env	*node;
	int		check;

	check = 0;
	node = malloc(sizeof(t_env));
	if (!node)				//error
		return (-1);
	if (check_equal_sign(export_var))
	{
		export_var = export_data(export_var);
		check = 1;
	}
	node->next = NULL;
	node->data = ft_strdup(export_var);
	if (check == 1)
		free(export_var);
	add_to_back_env(head, node);
	return (0);
}

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

void	add_to_back_env(t_env **head, t_env *node)
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
	free(temp);
	return ;
}

int		check_equal_sign(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '=')
		i++;
	if (str[i] == '=')
		return (i);			//was eerst 1
	return (-1);
}
