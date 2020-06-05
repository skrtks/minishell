/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <skorteka@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/07 12:32:29 by skorteka      #+#    #+#                 */
/*   Updated: 2020/06/05 15:28:26 by skorteka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "printf.h"
#include <stdarg.h>

t_flags				init_flags(void)
{
	t_flags flags;

	flags.minus = -1;
	flags.zero = -1;
	flags.hash = -1;
	flags.apo = -1;
	flags.space = -1;
	flags.plus = -1;
	flags.width = -1;
	flags.prec = -1;
	flags.l_mod = 0;
	flags.conv = 'q';
	return (flags);
}

t_flags				parse_l_mod(const char **format, t_flags flags)
{
	while (ft_strrchr("lh", *(*format)))
	{
		if (*(*format) == 'l')
			flags.l_mod += 1;
		if (*(*format) == 'h')
			flags.l_mod += 3;
		(*format)++;
	}
	flags.conv = *(*format);
	return (flags);
}

t_flags				parse_starwidth(t_flags flags, va_list args)
{
	int temp;

	temp = va_arg(args, int);
	if (temp < 0)
	{
		flags.minus = 1;
		flags.width = temp * -1;
	}
	else
		flags.width = temp;
	return (flags);
}

unsigned long long	get_dec_uns(t_flags flags, va_list args)
{
	unsigned long long num;

	if (flags.l_mod == 1)
		num = (unsigned long)va_arg(args, unsigned long);
	else if (flags.l_mod == 2)
		num = (unsigned long long)va_arg(args, unsigned long long);
	else if (flags.l_mod == 3)
		num = (unsigned short)va_arg(args, void*);
	else if (flags.l_mod == 6)
		num = (unsigned char)va_arg(args, void*);
	else
		num = (unsigned long long)va_arg(args, unsigned int);
	return (num);
}

long long			get_dec(t_flags flags, va_list args)
{
	long long num;

	if (flags.l_mod == 1)
		num = (long)va_arg(args, long);
	else if (flags.l_mod == 2)
		num = (long long)va_arg(args, long long);
	else if (flags.l_mod == 3)
		num = (short)va_arg(args, void*);
	else if (flags.l_mod == 6)
		num = (signed char)va_arg(args, void*);
	else
		num = (long long)va_arg(args, int);
	return (num);
}
