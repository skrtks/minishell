/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <skorteka@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 14:26:27 by mmourik       #+#    #+#                 */
/*   Updated: 2020/06/06 16:35:37 by skorteka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>
# include "./libft/libft.h"
# include "lexer.h"

t_node	*env(t_node *node, t_node *env_list);

#endif
