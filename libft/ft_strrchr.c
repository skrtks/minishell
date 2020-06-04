/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/02 12:55:07 by skorteka      #+#    #+#                 */
/*   Updated: 2019/11/02 12:55:09 by skorteka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char		*src;
	size_t			count;
	char			*ptr;

	ptr = NULL;
	src = s;
	count = 0;
	while (src[count] != '\0')
	{
		if (src[count] == c)
			ptr = (char *)s;
		count++;
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	else if (ptr != NULL)
		return (ptr);
	return (NULL);
}
