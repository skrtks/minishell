/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/02 13:10:54 by samkortekaa   #+#    #+#                 */
/*   Updated: 2020/07/12 15:10:54 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"

int	g_exitcode;

typedef struct	s_node
{
	struct s_node	*previous;
	char			*data;
	int				command;
	int				type;
	struct s_node	*next;
}				t_node;

typedef struct	s_env
{
	char			*data;
	struct s_env	*next;
}				t_env;

typedef struct	s_lists
{
	struct s_env		*env_list;
	struct s_env		*export_list;
}				t_lists;

typedef enum	e_commands
{
	ECHO = 0,
	CD = 1,
	PWD = 2,
	EXPORT = 3,
	UNSET = 4,
	ENV = 5,
	EXIT = 6,
	N = 7,
	SEMICOLON = 8,
	APOSTROPHE = 9,
	QUATATION_MARK = 10,
	ARROW_LEFT = 11,
	ARROW_RIGHT = 12,
	ARROW_DOUBLE = 13,
	PIPE = 14,
	PIPE_PLUS = 15,
	DOLLAR = 16,
	DOLLAR_QUESTION = 17,
	EXECUTABLE = 18,
	OTHER = 19,
}				t_commands;

typedef enum	e_type
{
	COMMAND = 0,
	FLAG = 1,
	SYMBOL = 2,
	ARGUMENT = 3,
	REDIR = 4,
	X = 5
}				t_type;

int		check_for_path(char **cmd, t_env *env_list);
int		new_node(t_node **head, char *cmd);
int		redirection(t_node *cmd_list);
int		setup_pipes(int n_pipes, int **fds);

t_node	*execute_cmd(t_node *node, t_lists **list);
t_node	*execute_in_pipe(t_node **ptr, int n_pipes, t_lists **list, int *fds);
t_node	*lexer(char *input, t_env *env_list);

void	parse (t_node *cmd_list, t_lists **list);

#endif
