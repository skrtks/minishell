/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sam <sam@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/12 12:02:16 by sam           #+#    #+#                 */
/*   Updated: 2020/06/12 14:28:06 by sam           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

#include "lexer.h"

t_node *execute(t_node *node, t_env *env_list);

#endif