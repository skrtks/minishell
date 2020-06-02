/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstlast_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/07 15:16:45 by skorteka      #+#    #+#                 */
/*   Updated: 2019/11/07 15:16:47 by skorteka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list *ptr;

	if (lst)
	{
		ptr = lst;
		while (ptr->next)
			ptr = ptr->next;
		return (ptr);
	}
	return (NULL);
}
