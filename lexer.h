/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/02 13:10:54 by samkortekaa   #+#    #+#                 */
/*   Updated: 2020/06/04 14:35:33 by merelmourik   ########   odam.nl         */
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

typedef struct	node_s {
				char *data;
				int command;
				int type;
				struct node_s *next;
}				node_t;

typedef enum	commands_e {
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
}				commands_t;


typedef enum	type_e {
				COMMAND = 0,
				ARGUMENT = 1,
				FLAG = 2,
				SYMBOL = 3,
}				type_t;

node_t			*lexer(char *input);
void			add_to_back(node_t **head, node_t *node);
void			free_list(node_t **head);
void			set_info(int command, int type, node_t *node);

#endif