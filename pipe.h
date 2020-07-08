/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/18 16:52:43 by sam           #+#    #+#                 */
/*   Updated: 2020/07/08 13:28:16 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H
# include "lexer.h"

int		count_pipes(t_node *cmd_list);
t_node	*execute_in_pipe(t_node **ptr, int n_pipes, t_lists **list, int *fds);
int		setup_pipes(int n_pipes, int **fds);
int		skip_to_cmd(t_node **ptr, int cmd_index);

void	check_type(t_node *ptr, int *type);
void	close_fds(int n_pipes, const int *fds);
void	exit_on_error(int *fds);

#endif