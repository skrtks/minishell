/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/17 10:31:41 by merelmourik   #+#    #+#                 */
/*   Updated: 2020/06/17 10:36:44 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include "../lexer.h"

t_node			*pwd(t_node *node);
t_node			*export_cmd(t_node *node, t_lists **list);

t_node	*cd(t_node *node, t_env *env_list);
t_node *echo(t_node *ptr);
void	exit_shell(t_node *command_list, t_env **env_list, t_env **export_list, int exit_code);
t_node	*unset(t_node *node, t_lists **list);
int		compare(const char *input, const char *in_list, int n);
void	remove_node(t_env **node_cur, t_env **node_prev, t_env **head);
t_node			*env(t_node *node, t_env *env_list);

#endif
