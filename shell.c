/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/29 11:46:04 by merelmourik   #+#    #+#                 */
/*   Updated: 2020/05/29 12:46:35 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int main(void)
{
	int   	ret;
	char	*input;
	// TODO: Turn off ctrl-c / ctrl-z / ctrl-d to prevent user exiting shell
	while (1)
	{
		write(1, "minishell> $ ", 13);
		ret = next_line(0, &input);
		if (ret == -1)
		{
			errno = 0;
			break ;
		}
		write(1, "minishell> $ ", 13);
		printf("+++ %s +++\n", input); // Remove
		// TODO: lexic analysis
		// TODO: Parse result of lexic analysis into "syntax tree/command table"
		// TODO: Execute "syntax tree/command table"
	}
	// TODO: Clean everything before returning
	return 0;
}