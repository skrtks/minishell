/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstsize_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/07 15:04:34 by skorteka      #+#    #+#                 */
/*   Updated: 2019/11/07 15:04:36 by skorteka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		len;
	t_list	*ptr;

	if (!lst)
		return (0);
	ptr = lst;
	len = 0;
	while (ptr)
	{
		len++;
		ptr = ptr->next;
	}
	return (len);
}
