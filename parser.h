/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 14:33:37 by samkortekaa   #+#    #+#                 */
/*   Updated: 2020/06/28 16:18:15 by mmourik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

void	parse(t_node *cmd_list, t_lists **list, t_io *io, t_fd *fd);
int		check_for_path(char **cmd, t_env *env_list);
void	redirection(t_node *cmd_list, t_fd *fd);
t_fd	*setup_fd(t_fd *fd);
void	reset_fd(int *std);

#endif
