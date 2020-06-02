/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/01 11:39:11 by skorteka      #+#    #+#                 */
/*   Updated: 2019/11/01 11:39:12 by skorteka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	ft_length(long n)
{
	long	len;

	if (n > 0)
		len = 0;
	else
	{
		len = 1;
		n = n * -1;
	}
	while (n >= 1)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static void		ft_convert(char *str, long input, size_t len)
{
	size_t	i;
	long	rem;

	i = len - 1;
	if (input == 0)
	{
		str[i] = '0';
		str[i + 1] = '\0';
		return ;
	}
	if (input < 0)
	{
		str[0] = '-';
		input = input * -1;
	}
	str[len] = '\0';
	while (input > 0)
	{
		rem = input % 10;
		str[i] = rem + '0';
		i--;
		input = input / 10;
	}
}

char			*ft_itoa(int n)
{
	char	*str;
	long	input;
	size_t	len;

	input = (long)n;
	len = ft_length(input);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_convert(str, input, len);
	return (str);
}
