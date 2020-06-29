/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/02 13:10:54 by samkortekaa   #+#    #+#                 */
/*   Updated: 2020/06/29 09:34:37 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>

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
	QUATATION_MARK = 10,		//deze kan er uit toch?
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
	REDIRECTION = 4,
	X = 5
}				t_type;

char			**free_array(char **array);
t_node			*lexer(char *input);



#endif
