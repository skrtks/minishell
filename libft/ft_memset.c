/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 09:33:57 by skorteka      #+#    #+#                 */
/*   Updated: 2019/10/29 09:34:06 by skorteka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t len)
{
	size_t			count;
	unsigned char	*s;

	s = (unsigned char	*)str;
	count = 0;
	while (count < len)
	{
		s[count] = (unsigned char)c;
		count++;
	}
	return (str);
}
