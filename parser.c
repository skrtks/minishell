/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <skorteka@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 14:33:37 by samkortekaa   #+#    #+#                 */
/*   Updated: 2020/07/02 13:01:38 by skorteka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins/builtins.h"
#include "parser.h"
#include "lexer.h"
#include "execute.h"
#include "expand.h"
#include "./libft/libft.h"
#include "pipe.h"

t_node	*execute_cmd(t_node *node, t_lists **list)
{
	if (node->command == ECHO)
		node = echo(node);
	else if (node->command == CD)
		node = cd(node, (*list)->env_list);
	else if (node->command == PWD)
		node = pwd(node);
	else if (node->command == EXPORT)
		node = export_cmd(node, list);
	else if (node->command == UNSET)
		node = unset(node, list);
	else if (node->command == ENV)
		node = env(node, (*list)->env_list);
	else if (node->command == EXECUTABLE)
		node = execute(node, (*list)->env_list);
	else if (node->command == EXIT)
		exit_shell(node, &(*list)->env_list, &(*list)->export_list, 0);
	else
	{
		if (check_for_path(&(node)->data, (*list)->env_list))
			node = execute(node, (*list)->env_list);
		else
		{
			node = node->next; // Skip to end or next semicolon
			write(1, "Command not recognized\n", 23);
		}
	}
	return (node);
}

void	parse(t_node *cmd_list, t_lists **list)
{
	t_node	*ptr;
	int		n_pipes;
	int		n_redirections;
	int		*fds;

	ptr = cmd_list;
	n_pipes = count_pipes(cmd_list);
	n_redirections = count_redirections(cmd_list);
	while (ptr)
	{
		if (n_redirections)
		{
			redirection(ptr, list, n_redirections);
			break ;
		}
		if (n_pipes)
		{
			if (setup_pipes(n_pipes, &fds))
				return ;		//error van maken
			execute_in_pipeline(&ptr, n_pipes, list, fds); // Check error?
		}
		else
			ptr = execute_cmd(ptr, list);
		if (ptr && ptr->type == SYMBOL)
			ptr = ptr->next;
		n_pipes = 0;
	}
}

// void	parse(t_node *cmd_list, t_lists **list)
// {
// 	t_node *ptr;
// 	int std[3];
	
// 	ptr = cmd_list;
// 	while (ptr)
// 	{
// 		redirection(cmd_list);
// 		ptr = execute_cmd(ptr, list);
// 		if (ptr && ptr->type == SYMBOL)
// 			ptr = ptr->next;
// 	}
// 	reset_fd(std);
// }
