/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sam <sam@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 14:26:27 by mmourik       #+#    #+#                 */
/*   Updated: 2020/06/10 14:45:33 by sam           ########   odam.nl         */
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

t_node		*export(t_node *node, t_node **env_list);
void	add_env_node(t_node **head, char *env_var);

#endif
