/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 11:00:33 by skorteka      #+#    #+#                 */
/*   Updated: 2019/10/30 11:00:36 by skorteka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	dst_l;
	size_t	src_l;

	src_l = ft_strlen(src);
	if (dstsize == 0)
		return (src_l);
	dst_l = ft_strlen(dst);
	i = dst_l;
	j = 0;
	while (src[j] && i < dstsize - 1)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	if (dst_l <= dstsize)
		dst[i] = '\0';
	if (dstsize >= dst_l)
		return (dst_l + src_l);
	else
		return (dstsize + src_l);
}
