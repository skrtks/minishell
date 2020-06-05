/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_3.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <skorteka@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/23 13:26:26 by skorteka      #+#    #+#                 */
/*   Updated: 2020/06/05 15:28:31 by skorteka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "printf.h"
#include <stdarg.h>

int			int_length(long long n)
{
	long long	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		n = n * -1;
	while (n < 0)
	{
		n = n / 10;
		len++;
	}
	while (n >= 1)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char		*set_case(char *str, t_flags flags)
{
	int i;

	i = 0;
	while (str[i] && flags.conv == 'X')
	{
		str[i] = ft_toupper(str[i]);
		i++;
	}
	while (str[i] && flags.conv == 'x')
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}

int			set_string(char **dst, char *src, int i)
{
	int j;

	j = 0;
	while (src[j])
	{
		*(*dst + i) = src[j];
		i++;
		j++;
	}
	return (i);
}

int			free_va_end(va_list args)
{
	va_end(args);
	return (-1);
}
