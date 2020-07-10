/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/26 11:27:21 by merelmourik   #+#    #+#                 */
/*   Updated: 2020/07/10 11:21:33 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int		check_equal_sign(const char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
		return (i);
	return (-1);
}

int check_invalid_id(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalpha(str[i]) && str[i] != '_')
		{
			ft_printf("minishell: export: `%s': not a valid identifier\n"
					, str);
			return (1);
		}
		i++;
	}
	return (0);
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
