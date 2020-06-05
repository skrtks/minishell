/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   i_print.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <skorteka@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/17 14:47:14 by skorteka      #+#    #+#                 */
/*   Updated: 2020/06/05 15:27:50 by skorteka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "printf.h"
#include <stdarg.h>
#include <unistd.h>

static t_length	get_length(t_flags flags, long long num)
{
	t_length len;

	len.sign = num < 0 ? '-' : '+';
	len.sign = (flags.space == 1 && flags.plus == -1 && num >= 0)
				? ' ' : len.sign;
	len.numlen = ((flags.prec == 0 && num == 0) ? 0 : int_length(num));
	len.numlen += (flags.apo == 1 ? sep_calculator(num) : 0);
	len.p_padlen = ((flags.prec != -1 && flags.prec >= len.numlen) ?
					flags.prec - len.numlen : 0);
	len.p_numlen = len.numlen + len.p_padlen;
	len.t_numlen = ((len.sign == '-' || (len.sign == '+' && flags.plus == 1)
					|| flags.space == 1) ? len.p_numlen + 1 : len.p_numlen);
	len.w_padlen = ((flags.width != -1 && flags.width >= len.t_numlen) ?
					flags.width - len.t_numlen : 0);
	len.total_len = len.t_numlen + len.w_padlen;
	return (len);
}

int				i_print(va_list args, t_flags flags)
{
	long long	num;
	t_length	len;
	int			slen;
	char		*str;

	num = get_dec(flags, args);
	flags.apo = (flags.apo == 1 ? 1 : 0);
	len = get_length(flags, num);
	str = create_dec_string(flags, len, num);
	if (!str)
		return (-1);
	slen = ft_strlen(str);
	write(1, str, slen);
	free(str);
	return (slen);
}
