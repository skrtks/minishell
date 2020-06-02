/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: samkortekaas <samkortekaas@student.codam.nl> +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/02 13:10:54 by samkortekaas  #+#    #+#                 */
/*   Updated: 2020/06/02 15:18:48 by samkortekaas  ########   odam.nl         */
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
				OTHER = 7
}				commands_t;

typedef enum	type_e {
				COMMAND = 0,
				ARGUMENT = 1,
				FLAG = 2
}				type_t;

node_t *lexer(char *input);

#endif