/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   other_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <skorteka@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/17 11:29:29 by merelmourik   #+#    #+#                 */
/*   Updated: 2020/07/01 15:03:25 by skorteka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_node	*free_on_error(char *cmd, t_node *cmd_list)
{
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
