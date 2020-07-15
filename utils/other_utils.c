/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   other_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/17 11:29:29 by merelmourik   #+#    #+#                 */
/*   Updated: 2020/07/14 13:49:03 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <string.h>
#include <errno.h>

t_node	*free_on_error(char *cmd, t_node *cmd_list)
{
	if (cmd)
		free(cmd);
	free_cmdlist(&cmd_list);
	return (NULL);
}

char	*check_spec_char(const char *str, int c)
{
	const char		*src;
	size_t			count;

	src = str;
	count = 0;
	while (src[count] != '\0')
	{
		if (src[count] == (char)c)
			return ((char *)str);
		count++;
		str++;
	}
	return (NULL);
}

void	err_msg(char *cmd, char *input, char *message)
{
	write(2, "minishell: ", 11);
	if (cmd)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
	}
	if (input)
	{
		write(2, input, ft_strlen(input));
		write(2, ": ", 2);
	}
	if (message)
	{
		write(2, message, ft_strlen(message));
		write(2, "\n", 2);
	}
	return ;
}
