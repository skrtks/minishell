/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmourik <mmourik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 14:26:27 by mmourik       #+#    #+#                 */
/*   Updated: 2020/06/06 12:51:09 by mmourik       ########   odam.nl         */
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

int			next_line(int fd, char **input);
int			word_count(char const *s);

#endif
