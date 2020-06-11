/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sam <sam@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/02 13:10:54 by samkortekaa   #+#    #+#                 */
/*   Updated: 2020/06/11 11:37:35 by mmourik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>

typedef struct	s_node
{
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
	DOLLAR = 15,
	DOLLAR_QUESTION = 16,
	OTHER = 17,
}				t_commands;

typedef enum	e_type
{
	COMMAND = 0,
	ARGUMENT = 1,
	FLAG = 2,
	SYMBOL = 3,
}				t_type;

t_node			*env(t_node *node, t_env *env_list);
t_node			*export_cmd(t_node *node, t_env **env_list);
t_node			*lexer(char *input);
t_node			*pwd(t_node *node);

int				add_env_node(t_env **head, char *env_var);
void			add_to_back(t_node **head, t_node *node);
void			add_to_back_env(t_env **head, t_env *node);
void			free_envlist(t_env **head);
void			free_cmdlist(t_node **head);
void			set_info(int command, int type, t_node *node);
void			continue_populating(char *cmd, t_node *node);
int				populate_node(char *cmd, t_node *node);


#endif
