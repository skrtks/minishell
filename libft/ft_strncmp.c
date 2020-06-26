/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 13:24:43 by skorteka      #+#    #+#                 */
/*   Updated: 2020/06/18 15:17:22 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			count;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char*)s1;
	str2 = (unsigned char*)s2;
	count = 0;
	while (count < n && (str1[count] != '\0' || str2[count] != '\0'))
	{
		if (str1[count] != str2[count])
			return (-1);
		count++;
	}
	return (0);
}
