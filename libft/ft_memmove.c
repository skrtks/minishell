/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 15:21:19 by skorteka      #+#    #+#                 */
/*   Updated: 2019/10/29 15:21:21 by skorteka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dest;
	const unsigned char	*source;

	if (dst == NULL && src == NULL)
		return (dst);
	dest = dst;
	source = src;
	if (source < dest)
	{
		while (len)
		{
			len--;
			dest[len] = source[len];
		}
		return (dst);
	}
	while (len)
	{
		*dest = *source;
		dest++;
		source++;
		len--;
	}
	return (dst);
}
