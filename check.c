/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sam <sam@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/07 21:11:33 by sam           #+#    #+#                 */
/*   Updated: 2020/07/07 22:13:57 by sam           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "lexer.h"
#include "utils/utils.h"

int check_redir(const t_node *ptr) {
	if (ptr->type == REDIR && ptr->next == NULL)
	{
		ft_printf("minishell: syntax error near unexpected token `newline'\n");
			return (1);
	}
	return (0);
}

int check_cmd_list(t_node *cmd_list)
{
	t_node	*ptr;
	int		prev_is_symbol;
	int		prev_is_red;
	int 	new_cmd;

	ptr = cmd_list;
	prev_is_symbol = 1;
	prev_is_red = 0;
	new_cmd = 1;
	while (ptr)
	{
		if (check_redir(ptr))
			return (1); // Exit code? in bash 2 bij syntax error
		if ((ptr->type == SYMBOL && (prev_is_symbol || prev_is_red)) ||
			(ptr->type == REDIR && (prev_is_red) && !new_cmd))
		{
			ft_printf("minishell: syntax error near unexpected token `%s'\n", ptr->data);
			return (1); // Exit code? in bash 2 bij syntax error
		}
		else if (ptr->type == SYMBOL)
		{
			prev_is_red = 0;
			prev_is_symbol = 1;
		}
		else if (ptr->type == REDIR)
		{
			prev_is_symbol = 0;
			prev_is_red = 1;
		}
		else
		{
			prev_is_symbol = 0;
			prev_is_red = 0;
		}
		ptr = ptr->next;
		if (ptr && ptr->command == SEMICOLON)
			new_cmd = 1;
		else
			new_cmd = 0;
	}
	return (0);
}