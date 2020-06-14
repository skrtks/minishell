/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/11 13:21:54 by skorteka      #+#    #+#                 */
/*   Updated: 2020/06/14 16:32:49 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNSET_H
# define UNSET_H

# include "lexer.h"

t_node	*unset(t_node *node, t_lists **list);
int		compare(const char *input, const char *in_list, int n);
void	remove_node(t_env **node_cur, t_env **node_prev, t_env **head);

#endif
