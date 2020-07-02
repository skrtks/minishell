/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <skorteka@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 14:33:37 by samkortekaa   #+#    #+#                 */
/*   Updated: 2020/07/02 13:42:44 by skorteka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

void	parse (t_node *cmd_list, t_lists **list);
int		check_for_path(char **cmd, t_env *env_list);
t_node	*execute_cmd(t_node *node, t_lists **list);
void	redirection(t_node *cmd_list, int i);
void	reset_fd(int *std);
int		new_node(t_node **head, char *cmd);
int		count_redirections(t_node *cmd_list);

#endif
