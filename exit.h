/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/09 15:21:39 by sam           #+#    #+#                 */
/*   Updated: 2020/06/11 18:15:52 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_H
# define EXIT_H

#include "lexer.h"

void	exit_shell(t_node *command_list, t_env **env_list, t_env **export_list, int exit_code);

#endif