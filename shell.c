/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sam <sam@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/09 11:23:06 by sam           #+#    #+#                 */
/*   Updated: 2020/06/18 17:40:57 by sam           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "lexer.h"
#include "parser.h"
#include "libft/libft.h"
#include "utils/utils.h"
#include "pipe.h"

t_lists	*get_env(char **envp)
{
	t_lists	*list;

	if (!(list = malloc(sizeof(t_lists))))
		return (NULL);
	list->env_list = NULL;
	list->export_list = NULL;
	while (*envp)
	{
		if (add_env_node(&list->env_list, *envp))
			return (NULL);
		if (add_export_node(&list->export_list, *envp))
			return (NULL);
		envp++;
	}
	return (list);
}

void	sig_handler()
{
	ft_printf("\nminishell> $ ");
}

int		main(int argc, char **argv, char **envp)
{
	int		ret;
	char	*input;
	t_node	*command_list;
	t_lists	*list;
	t_io	*io;

	io = malloc(sizeof(t_io));
	if (!io)
		return (1);
	io = setup_io(io);
	list = get_env(envp);
	// signal(SIGINT, sig_handler);
	// signal(SIGQUIT, sig_handler);
	// signal(SIGTSTP, sig_handler);
	if (!list)
	{
		printf("Error starting, env could not be loaded. \nTerminating...\n");
		exit(1);
	}
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
		free(input);
		input = NULL;
		parse(command_list, &list, io);
		free_cmdlist(&command_list);
	}
	(void) argc;
	(void) argv;
	return (0);
}
