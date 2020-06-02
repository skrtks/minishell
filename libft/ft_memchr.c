/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 16:21:43 by skorteka      #+#    #+#                 */
/*   Updated: 2019/10/29 16:21:45 by skorteka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		*src;
	unsigned char		needle;
	size_t				count;

	needle = (unsigned char)c;
	count = 0;
	src = (unsigned char *)s;
	while (count < n)
	{
		if (src[count] == (unsigned char)c)
			return ((unsigned char *)s);
		count++;
		s++;
	}
	return (NULL);
}
