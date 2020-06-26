/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/06 15:41:37 by mmourik       #+#    #+#                 */
/*   Updated: 2020/06/26 10:32:47 by merelmourik   ########   odam.nl         */
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

int	compare_exp(const char *input, const char *in_list)
{
	int i;

	i = 0;
	while (input[i] != '\0' && in_list[i] != '\0')
	{
		if (input[i] == '\0')
			return (-1);
		if (input[i] == '=' && in_list[i] == '\0')
			return (1);
		if (input[i] == '=' && in_list[i] == '=')
			return (1);
		if (input[i] != in_list[i])
			return (-1);
		i++;
	}
	if (input[i] == '\0' && in_list[i] == '=')
		return (2);
	return (1);
}

void			check_existence_env(char *str, t_env **list)
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

int			check_existence_exp(char *input, t_env **head)
{
	t_env	*ptr;
	t_env	*previous;

	ptr = *head;
	previous = NULL;
	while (ptr)
	{
		if (compare_exp(input, ptr->data) == 1)
		{
			remove_node(&ptr, &previous, head);
			return (0);
		}
		if (compare_exp(input, ptr->data) == 2)
			return (-1);
		previous = ptr;
		ptr = ptr->next;
	}
	return (0);
}

int			input_check(char *str, char c)
{
	int i;

	while (str[i])
	{
		if (str[i] == c)
			return (-1);
		i++;
	}
	return (0);
}

t_node		*check_input(t_node *node)
{
	int i;			//als je hier een *t_node van maakt word de code beter en korter
	int len;
	char *str1 = "!";
	char *str2 = "@^*+={}[]:,./?~";		//niet=
	char *str3 = "()";
	i = 0;
	len = ft_strlen(node->data) - 1;
	
	if (!(input_check()))
	while (str1[i])
	{
		if (node->data[0] == str1[i])
			ft_printf("minishell: %s: event not found\n", node->data);
		i++;
	}
	i = 0;
	while (str2[i])
	{
		if (node->data[0] == str2[i] || (node->data[len] == str2[i] && str2[i] != '=')\
		|| (i == len && node->data[len] == '!'))
			ft_printf("minishell: export: '%s': not a valid identifier\n", node->data);
		i++;
	}
	i = 0;
	while (str3[i])
	{
		if (node->data[0] == str3[i] || (node->data[len] == str3[i]))
			ft_printf("minishell: syntax error near unexpected token %s\n", node->data);
		i++;
	}
	//deze negeert hij en haalt hij weg aan het begin vd string: #\
	//deze doet hij helemaal niks mee: $
	//deze doet vaag: &
	//checken of deze niet al bij pipe wordt verwerkt |
	//str[0] bij redirections opvangen
	return (node);
}

t_node			*extend_lists(t_node *node, t_lists **list)
{
	int		i;
	char	*temp;

	while (node->next != NULL && node->next->command != SEMICOLON)
	{
		node = node->next;
		temp = ft_strdup(node->data);
		i = check_existence_exp(node->data, &(*list)->export_list);
		check_input(node);
		if (check_equal_sign(node->data) > 0)
		{
			if (node->next != NULL)
			{
				free (temp);
				temp = ft_strjoin(node->data, node->next->data);
				node = node->next;
			}
			check_existence_env(temp, &(*list)->env_list);
			add_env_node(&(*list)->env_list, temp);
		}
		if (i != -1)
			add_export_node(&(*list)->export_list, temp);
		free(temp);
	}
	return (node->next);
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
