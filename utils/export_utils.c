/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/26 11:27:21 by merelmourik   #+#    #+#                 */
/*   Updated: 2020/07/09 20:19:07 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int		check_equal_sign(const char *str)
{
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '=')
		i++;
	j = i + 1;
	while (str[j])
	{
		if (ft_isalnum(str[j]) == 0 && str[j] != '_')
		{
			//ft_printf("minishell: export: '%s': not a valid identifier\n", str);
			return (-2);
		}
		j++;
	}
	if (str[i] == '=')
		return (i);
	return (-1);
}

int		input_check(char c, char *str1)		//in hoeverre willen we dit gaan doen?
{
	char	*str;
	int		i;

	i = 0;
	str = "@^*+{}[]:,./?~";
	if (str1[0] == '=' || str1[(ft_strlen(str1) - 1)] == '!')
		return (-1);
	while (str[i])
	{
		if (str[i] == c)
			return (-1);
		i++;
	}
	return (0);
}

t_node	*check_input(t_node *node)		//selfcalling functie van maken
{
	int i;

	i = 0;
	while (node->data[i])
	{
		if (node->data[i] == ')' || node->data[i] == '(')
		{
			ft_printf("minishell: syntax error near unexpected token %s\n",\
			node->data);
			return (node);
		}
		i++;
	}
	i = 0;
	while (node->data[i])
	{
		if (input_check(node->data[i], node->data) == -1)
		{
			ft_printf("minishell: export: '%s': not a valid identifier\n",\
			node->data);
			return (node);
		}
		i++;
	}
	if (node->data[0] == '!' || node->data[0] == '|')
		ft_printf("minishell: %s: event not found\n", node->data);
	return (node);
}

int		compare_exp(const char *input, const char *in_list)
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

int		compare_data(const char *str1, const char *str2)
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
