/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memccpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 11:58:55 by skorteka      #+#    #+#                 */
/*   Updated: 2019/10/29 11:58:56 by skorteka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t				count;
	unsigned char		*dest;
	unsigned char		*source;
	unsigned char		needle;

	dest = (unsigned char *)dst;
	source = (unsigned char *)src;
	needle = (unsigned char)c;
	count = 0;
	while (source[count] != needle && count < n)
	{
		dest[count] = source[count];
		count++;
	}
	if (source[count] == needle)
	{
		dest[count] = source[count];
		return (&dst[count + 1]);
	}
	else
		return (NULL);
}
