/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 10:26:43 by skorteka      #+#    #+#                 */
/*   Updated: 2019/10/29 10:26:44 by skorteka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			count;
	unsigned char	*dest;
	const char		*source;

	dest = dst;
	source = src;
	count = 0;
	if (dst == NULL && src == NULL)
		return (dst);
	while (count < n)
	{
		dest[count] = source[count];
		count++;
	}
	return (dst);
}
