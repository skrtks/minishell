/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sam <sam@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/17 16:26:57 by sam           #+#    #+#                 */
/*   Updated: 2020/06/17 16:28:31 by sam           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIP_H
# define PIP_H

#include "lexer.h"

int set_pipes(t_node *cmd_list, int *pipe_before, t_io *io);
t_io *set_up_pipe(void);

#endif
