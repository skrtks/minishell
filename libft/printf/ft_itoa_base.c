/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa_base.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/01 11:39:11 by skorteka      #+#    #+#                 */
/*   Updated: 2019/11/01 11:39:12 by skorteka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	ft_length(long long n, int base)
{
	long long	len;

	if (n > 0)
		len = 0;
	else
	{
		len = 1;
		n = n * -1;
	}
	while (n < 0)
	{
		n = n / base;
		len++;
	}
	while (n >= 1)
	{
		n = n / base;
		len++;
	}
	return (len);
}

static size_t	ft_length_uns(unsigned long long n, int base)
{
	long long	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n >= 1)
	{
		n = n / base;
		len++;
	}
	return (len);
}

static void		set_sign(long long num, int base, char **ptr)
{
	if (num < 0 && base == 10)
	{
		(*ptr)--;
		*(*ptr) = '-';
	}
}

char			*itoa_b(long long value, int base)
{
	char		*set;
	char		*ptr;
	long long	num;

	ptr = malloc((ft_length(value, base) + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	set = "0123456789abcdef";
	ptr += ft_length(value, base);
	*ptr = '\0';
	num = value;
	value *= ((value < 0 && base == 10) ? -1 : 1);
	if (value == 0)
	{
		ptr--;
		*ptr = set[value % base];
	}
	while (value != 0)
	{
		ptr--;
		*ptr = (value < 0 ? set[(value % base) * -1] : set[value % base]);
		value /= base;
	}
	set_sign(num, base, &ptr);
	return (ptr);
}

char			*itoa_b_uns(unsigned long long value, int base)
{
	char				*set;
	char				*ptr;
	unsigned long long	num;

	ptr = malloc((ft_length_uns(value, base) + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	set = "0123456789abcdef";
	ptr += ft_length_uns(value, base);
	*ptr = '\0';
	num = value;
	value *= ((value < 0 && base == 10) ? -1 : 1);
	if (value == 0)
	{
		ptr--;
		*ptr = set[value % base];
	}
	while (value != 0)
	{
		ptr--;
		*ptr = set[value % base];
		value /= base;
	}
	return (ptr);
}
