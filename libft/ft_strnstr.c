/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 12:24:30 by skorteka      #+#    #+#                 */
/*   Updated: 2019/10/30 12:24:32 by skorteka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (*needle == '\0')
		return ((char *)haystack);
	i = 0;
	j = 0;
	while (haystack[i] && i < len)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && i + j < len)
		{
			if (haystack[i + j] == needle[j] && needle[j + 1] == '\0')
				return ((char *)haystack + i);
			else if (haystack[i + j + 1] != needle[j + 1]
					&& needle[j + 1] != '\0')
				break ;
			j++;
		}
		i++;
	}
	return (NULL);
}
