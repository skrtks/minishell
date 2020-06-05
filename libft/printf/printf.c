/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printf.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <skorteka@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/11 09:31:07 by skorteka      #+#    #+#                 */
/*   Updated: 2020/06/05 15:28:04 by skorteka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "printf.h"
#include <stdarg.h>
#include <unistd.h>

static int		convert(const char **format, va_list args, t_flags flags)
{
	int output;

	if (*(*format) == 'c' || *(*format) == '%')
		output = c_print(args, flags);
	if (*(*format) == 's')
		output = s_print(args, flags);
	if (*(*format) == 'i' || *(*format) == 'd')
		output = i_print(args, flags);
	if (*(*format) == 'u')
		output = u_print(args, flags);
	if (*(*format) == 'X' || *(*format) == 'x')
		output = x_print(args, flags);
	if (*(*format) == 'p')
		output = p_print(args, flags);
	(*format)++;
	return (output);
}

static t_flags	parse_flags(const char **format)
{
	t_flags flags;

	flags = init_flags();
	while (ft_strrchr("-0#\' +", *(*format)))
	{
		if (*(*format) == '-')
			flags.minus = 1;
		if (*(*format) == '0')
			flags.zero = 1;
		if (*(*format) == '#')
			flags.hash = 1;
		if (*(*format) == '\'')
			flags.apo = 1;
		if (*(*format) == ' ')
			flags.space = 1;
		if (*(*format) == '+')
			flags.plus = 1;
		(*format)++;
	}
	return (flags);
}

static void		parse_other(const char **format, va_list args, t_flags *flags)
{
	int temp;

	if (*(*format) == '*')
		*flags = parse_starwidth(*flags, args);
	else if (!ft_strrchr("cspdiuxX%.", *(*format)))
		flags->width = ft_atoi(*format);
	while (!ft_strrchr("cspdiuxXlh%.", *(*format)))
		(*format)++;
	if (*(*format) == '.')
	{
		(*format)++;
		if (*(*format) == '*')
		{
			temp = va_arg(args, int);
			flags->prec = (temp < 0 ? -1 : temp);
		}
		else if (ft_strrchr("cspdiuxX%", *(*format)))
			flags->prec = 0;
		else if (!ft_strrchr("cspdiuxX%", *(*format)))
			flags->prec = ft_atoi(*format);
	}
	while (!ft_strrchr("cspdiuxXlh%", *(*format)))
		(*format)++;
	if (flags->zero == 1 && flags->minus == 1)
		flags->zero = -1;
}

static int		write_string(const char **format)
{
	int		s_ind;

	s_ind = 0;
	while (*(*format) != '%' && *(*format))
	{
		write(1, *format, 1);
		s_ind++;
		(*format)++;
	}
	return (s_ind);
}

int				ft_printf(const char *format, ...)
{
	va_list	args;
	t_flags	flags;
	int		output;
	int		convert_out;

	output = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format != '%')
			output += write_string(&format);
		if (*format == '%')
		{
			format++;
			flags = parse_flags(&format);
			parse_other(&format, args, &flags);
			flags = parse_l_mod(&format, flags);
			convert_out = convert(&format, args, flags);
			if (convert_out == -1)
				return (free_va_end(args));
			output += convert_out;
		}
	}
	va_end(args);
	return (output);
}
