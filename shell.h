/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/29 11:43:24 by merelmourik   #+#    #+#                 */
/*   Updated: 2020/05/29 15:05:59 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>

typedef struct s_shell
{
	/* data */
}				t_shell;

int			next_line(int fd, char **input);
char		**ft_split(char const *s);