/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sam <sam@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/18 16:52:43 by sam           #+#    #+#                 */
/*   Updated: 2020/06/18 17:07:07 by sam           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H
#include "lexer.h"

t_io *setup_io(t_io *io);
t_io *pipe_sequence(t_node *cmd_list, t_io *io);

#endif