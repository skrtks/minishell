/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear_bonus.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/08 09:37:30 by skorteka      #+#    #+#                 */
/*   Updated: 2019/11/08 09:37:32 by skorteka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *ptr;
	t_list *tmp;

	ptr = *lst;
	while (ptr)
	{
		(*del)(ptr->content);
		tmp = ptr;
		ptr = ptr->next;
		free(tmp);
	}
	*lst = NULL;
}
