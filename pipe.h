/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/18 16:52:43 by sam           #+#    #+#                 */
/*   Updated: 2020/06/29 09:27:34 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H
#include "lexer.h"

int execute_in_pipeline(t_node **ptr, int n_pipes, t_lists **list, int *fds);
int count_pipes(t_node *cmd_list);
int setup_pipes(int n_pipes, int **fds);

#endif