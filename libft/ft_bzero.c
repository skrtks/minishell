/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sam <sam@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 10:19:23 by skorteka      #+#    #+#                 */
/*   Updated: 2020/06/20 14:42:56 by sam           ########   odam.nl         */
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
