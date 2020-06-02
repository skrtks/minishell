/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 10:19:23 by skorteka      #+#    #+#                 */
/*   Updated: 2019/10/29 10:19:24 by skorteka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t len)
{
	size_t			count;
	unsigned char	*str;

	str = s;
	count = 0;
	while (count < len)
	{
		str[count] = '\0';
		count++;
	}
}
