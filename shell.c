/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <skorteka@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/29 11:46:04 by merelmourik   #+#    #+#                 */
/*   Updated: 2020/06/06 15:32:50 by skorteka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "lexer.h"
#include "parser.h"

int	main(int argc, char **argv, char **envp)
{
	int		ret;
	char	*input;
	t_node	*command_list;

	while (1)
	{
		write(1, "minishell> $ ", 13);
		ret = get_next_line(0, &input);
		if (ret == -1)
		{
			errno = 0;
			break ;
		}
		command_list = lexer(input);
		parse(command_list, envp);
		free_list(&command_list);
	}
	argc = 0;
	argv = NULL;
	return (0);
}
