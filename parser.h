/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 14:33:37 by samkortekaa   #+#    #+#                 */
/*   Updated: 2020/07/09 20:33:19 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

int		check_for_path(char **cmd, t_env *env_list);
int		count_redirections(t_node *cmd_list);
int		new_node(t_node **head, char *cmd);
int		redirection(t_node *cmd_list);

t_node	*execute_cmd(t_node *node, t_lists **list);

void	parse (t_node *cmd_list, t_lists **list);
void	reset_fd(int *std);

#endif
