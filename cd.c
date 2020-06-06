/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <skorteka@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/06 13:52:18 by skorteka      #+#    #+#                 */
/*   Updated: 2020/06/06 14:18:41 by skorteka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"
#include "shell.h"
#include "./libft/libft.h"
#include "errno.h"
#include <unistd.h>


t_node *cd(t_node *node)
{
	char *path;

	node = node->next;
	if (!node)
		return (node);
	path = node->data;
	if (chdir(path))
	{
		ft_printf("Error: %s", strerror(errno));
		errno = 0;
	}
	return (node);
}