/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sam <sam@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/18 16:52:43 by sam           #+#    #+#                 */
/*   Updated: 2020/07/01 15:26:03 by mmourik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H
#include "lexer.h"

int execute_in_pipeline(t_node **ptr, int n_pipes, t_lists **list, int *fds);
int count_pipes(t_node *cmd_list);
void exit_on_error(int *fds);
void close_fds(int n_pipes, const int *fds);
void check_type(t_node *ptr, int *type);
int skip_to_cmd(t_node **ptr, int cmd_index);
int setup_pipes(int n_pipes, int **fds);

#endif