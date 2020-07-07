/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sam <sam@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/07 21:11:33 by sam           #+#    #+#                 */
/*   Updated: 2020/07/07 22:02:05 by sam           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "lexer.h"
#include "utils/utils.h"
#include "expand.h"

int check_cmd_list(t_node *cmd_list)
{
	t_node *ptr;
	int		prev_is_symbol;
	int		prev_is_red;

	ptr = cmd_list;
	prev_is_symbol = 1;
	prev_is_red = 0;
	while (ptr)
	{
		if ((ptr->type == SYMBOL && prev_is_symbol) || (ptr->type == REDIR && prev_is_red))
		{
			ft_printf("minishell: syntax error near unexpected token `%s'\n", ptr->data);
			return (1);
		}
		else if (ptr->type == SYMBOL)
			prev_is_symbol = 1;
		else if (ptr->type == REDIR)
			prev_is_red = 1;
		else
		{
			prev_is_symbol = 0;
			prev_is_red = 0;
		}
		ptr = ptr->next;
	}
	return (0);
}