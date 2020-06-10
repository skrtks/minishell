/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sam <sam@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/09 15:21:39 by sam           #+#    #+#                 */
/*   Updated: 2020/06/10 16:00:13 by sam           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_H
# define EXIT_H

#include "lexer.h"

void exit_shell(t_node *command_list, t_node **env_list, int exit_code);

#endif