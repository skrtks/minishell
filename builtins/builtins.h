/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/17 10:31:41 by merelmourik   #+#    #+#                 */
/*   Updated: 2020/07/12 12:13:44 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include "utils/utils.h"
# include "libft/libft.h"

int		compare(const char *input, const char *in_list, int n);

t_node	*cd(t_node *node, t_lists **list);
t_node	*echo(t_node *ptr);
t_node	*env(t_node *node, t_env *env_list);
t_node	*export_cmd(t_node *node, t_lists **list);
t_node	*pwd(t_node *node);
t_node	*unset(t_node *node, t_lists **list);

void	check_existence_env(char *str, t_env **list);
void	exit_shell(t_node *cmd_lst, t_env **env_lst, t_env **exp_lst, int code);
void	remove_node(t_env **node_cur, t_env **node_prev, t_env **head);

#endif
