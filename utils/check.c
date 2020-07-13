/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/07 21:11:33 by sam           #+#    #+#                 */
/*   Updated: 2020/07/12 12:18:12 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	check_redir(const t_node *ptr)
{
	if (ptr->type == REDIR && ptr->next == NULL)
	{
		err_message(NULL, NULL,
				"syntax error near unexpected token `newline'");
		g_exitcode = 2;
		return (1);
	}
	return (0);
}

static int	check_current(const t_node *ptr, int *prev_is_symbol, \
			int *prev_is_red, const int *new_cmd)
{
	if ((ptr->type == SYMBOL && (*prev_is_symbol || *prev_is_red)) ||
	(ptr->type == REDIR && (*prev_is_red) && !*new_cmd))
	{
		write(2, "minishell: syntax error near unexpected token `", 47);
		write(2,	ptr->data, ft_strlen(ptr->data));
		write(2, "'\n", 2);
		g_exitcode = 2;
		return (1);
	}
	else if (ptr->type == SYMBOL)
	{
		*prev_is_red = 0;
		*prev_is_symbol = 1;
	}
	else if (ptr->type == REDIR)
	{
		*prev_is_symbol = 0;
		*prev_is_red = 1;
	}
	else
	{
		*prev_is_symbol = 0;
		*prev_is_red = 0;
	}
	return (0);
}

int			check_cmd_list(t_node *cmd_list)
{
	t_node	*ptr;
	int		prev_is_symbol;
	int		prev_is_red;
	int		new_cmd;

	ptr = cmd_list;
	prev_is_symbol = 1;
	prev_is_red = 0;
	new_cmd = 1;
	g_exitcode = 0;
	while (ptr)
	{
		if (check_redir(ptr))
			return (1);
		if (check_current(ptr, &prev_is_symbol, &prev_is_red, &new_cmd))
			return (1);
		ptr = ptr->next;
		if (ptr && ptr->command == SEMICOLON)
			new_cmd = 1;
		else
			new_cmd = 0;
	}
	return (0);
}
