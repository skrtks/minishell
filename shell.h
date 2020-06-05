/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: samkortekaas <samkortekaas@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/29 11:43:24 by merelmourik   #+#    #+#                 */
/*   Updated: 2020/06/05 13:57:14 by mmourik       ########   odam.nl         */
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

int			next_line(int fd, char **input);
int			word_count(char const *s);

#endif