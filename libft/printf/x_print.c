/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   x_print.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <skorteka@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/23 14:18:27 by skorteka      #+#    #+#                 */
/*   Updated: 2020/06/05 15:28:35 by skorteka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "printf.h"
#include <stdarg.h>
#include <unistd.h>

static t_length	get_length(t_flags flags, unsigned long long num)
{
	t_length	len;
	char		*str;

	str = itoa_b_uns(num, 16);
	len.sign = '+';
	len.numlen = ((flags.prec == 0 && num == 0) ? 0 : ft_strlen(str));
	len.p_padlen = ((flags.prec != -1 && flags.prec >= len.numlen) ?
					flags.prec - len.numlen : 0);
	len.t_numlen = len.numlen + len.p_padlen;
	len.w_padlen = ((flags.width != -1 && flags.width >= len.t_numlen) ?
					flags.width - len.t_numlen : 0);
	len.total_len = len.t_numlen + len.w_padlen;
	if (flags.hash == 1)
	{
		len.w_padlen = (len.w_padlen - 2 < 0 ? 0 : len.w_padlen - 2);
		len.total_len = len.t_numlen + len.w_padlen + 2;
	}
	free(str);
	return (len);
}

static void		fill_width(t_flags flags, t_length len, int *i, char **str)
{
	int extra_for_hash;

	*i = 0;
	if (flags.minus == -1 && flags.zero == '0' && flags.hash == 1)
	{
		(*str)[*i] = '0';
		(*i)++;
		(*str)[*i] = 'x';
		(*i)++;
	}
	if (flags.minus == -1)
	{
		ft_memset(((*str) + *i), flags.zero, len.w_padlen);
		(*i) += len.w_padlen;
	}
	if (flags.minus == 1)
	{
		extra_for_hash = (flags.hash == 1 ? 2 : 0);
		ft_memset(((*str) + extra_for_hash + len.t_numlen),
				flags.zero, len.w_padlen);
	}
}

static char		*create_string(t_flags flags, t_length len,
								unsigned long long num)
{
	char	*str;
	char	*num_str;
	int		i;

	str = malloc((len.total_len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	num_str = itoa_b_uns(num, 16);
	if (!num_str)
		return (NULL);
	flags.zero = ((flags.prec == -1 && flags.zero == 1) ? '0' : ' ');
	fill_width(flags, len, &i, &str);
	if (flags.zero == ' ' && flags.hash == 1)
		i = set_string(&str, "0x", i);
	ft_memset((str + i), '0', len.p_padlen);
	i += len.p_padlen;
	if (!(flags.prec == 0 && num == 0))
		i = set_string(&str, num_str, i);
	if (flags.minus == 1)
		i += len.w_padlen;
	str[i] = '\0';
	free(num_str);
	return (str);
}

int				x_print(va_list args, t_flags flags)
{
	unsigned long long	num;
	t_length			len;
	int					slen;
	char				*str;

	num = get_dec_uns(flags, args);
	flags.hash = (flags.hash == 1 && num != 0 ? 1 : 0);
	len = get_length(flags, num);
	str = create_string(flags, len, num);
	if (!str)
		return (-1);
	str = set_case(str, flags);
	slen = ft_strlen(str);
	write(1, str, slen);
	if (str)
		free(str);
	return (slen);
}
