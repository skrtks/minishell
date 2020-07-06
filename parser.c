/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 14:33:37 by samkortekaa   #+#    #+#                 */
/*   Updated: 2020/07/06 14:50:45 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins/builtins.h"
#include "parser.h"
#include "lexer.h"
#include "execute.h"
#include "expand.h"
#include "./libft/libft.h"
#include "pipe.h"
#include <fcntl.h>
#include <sys/stat.h>

t_node	*execute_cmd(t_node *node, t_lists **list)
{
	struct stat buf;

	if (node->type == REDIR)
	{
		if (node->next == NULL)
		{
			ft_printf("minishell: syntax error near unexpected token `newline'\n");
			return (node);
		}
		if (node->command == ARROW_LEFT)
			if (stat(node->next->data, &buf) == -1)
				ft_printf("minishell: %s: No such file or directory\n", node->next->data);
		return (node->next->next);
	}
	if (node->command == ECHO)
		node = echo(node);
	else if (node->command == CD)
		node = cd(node, list);
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
			node = node->next;		//hier kunnen we als we willen makkelijke een syntax error van maken| 
			write(1, "Command not found\n", 23);
		}
	}
	if (node && node->type == REDIR)
		while (node && node->type != SYMBOL)
			node = node->next;
	return (node);
}

void	parse(t_node *cmd_list, t_lists **list)
{
	t_node	*ptr;
	int		n_pipes;
	int		n_redirections;
	int		*fds;
	int		ori_out;
	int		ori_in;

	ori_out = dup(1);
	ori_in = dup(0);
	ptr = cmd_list;
	n_pipes = count_pipes(cmd_list);
	n_redirections = count_redirections(cmd_list);
	while (ptr)
	{
		if (n_redirections)
			redirection(ptr);
		if (n_pipes)
		{
			if (setup_pipes(n_pipes, &fds))
				return ;		//error van maken
			execute_in_pipe(&ptr, n_pipes, list, fds); // Check error?
		}
		else
			ptr = execute_cmd(ptr, list);
		if (ptr && (ptr->type == SYMBOL || ptr->type == REDIR))
			ptr = ptr->next;
		n_pipes = 0;
	}
	dup2(ori_out, 1);
	dup2(ori_in, 0);
}

//exit code 0 - 255

// else if (str[0] == '>' && str[1] == '>' && str[2] == '|' && str[3] == '|')
// 		ft_printf("minishell: syntax error near unexpected token `||'\n");
// 	else if (str[0] == '>' && str[1] == '>' && str[2] == '|')
// 		ft_printf("minishell: syntax error near unexpected token `|'\n");
// 	else if (str[0] == '>' && str[1] == '|')
		// ft_printf("minishell: syntax error near unexpected token `newline'\n");

//bovenstaande kan ik wel implementeren, maar is niet echt de moeite waard denk ik
//en het is veel moeite omdat de norme dan echt in de weg gaat zitten
