/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_1.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <skorteka@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/06 15:48:44 by skorteka      #+#    #+#                 */
/*   Updated: 2020/06/05 15:28:21 by skorteka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "printf.h"
#include <stdarg.h>
#include <locale.h>

int				sep_calculator(long long num)
{
	long long	len;

	len = 0;
	if (num < 0)
		num *= -1;
	while (num >= 1000)
	{
		num = num / 1000;
		len++;
	}
	return (len);
}

char			*set_separators(long long num, t_length len,
								char *str, int start)
{
	int				i;
	struct lconv	*lc;

	lc = localeconv();
	i = start + len.numlen;
	if (num < 0)
		num *= -1;
	while (num >= 1000)
	{
		i -= 4;
		str[i] = *lc->thousands_sep;
		num /= 1000;
	}
	return (str);
}

char			*set_num(char *str, char *num_str,
						t_index *index)
{
	while (num_str[index->j])
	{
		if (str[index->i] == '\0')
		{
			str[index->i] = num_str[index->j];
			index->j++;
		}
		(index->i)++;
	}
	return (str);
}

static void		fill_width(t_flags flags, t_length len, t_index *index,
							char **str)
{
	index->i = 0;
	if ((len.sign == '-' || flags.plus == 1 || flags.space == 1)
		&& flags.zero == '0' && flags.minus == -1 && flags.conv != 'u')
	{
		(*str)[index->i] = len.sign;
		(index->i)++;
	}
	if (flags.minus == -1)
	{
		ft_memset(((*str) + index->i), flags.zero, len.w_padlen);
		(index->i) += len.w_padlen;
	}
	if ((len.sign == '-' || flags.plus == 1 || flags.space == 1)
		&& (flags.zero == ' ') && flags.conv != 'u')
	{
		(*str)[index->i] = len.sign;
		(index->i)++;
	}
	if (flags.minus == 1)
		ft_memset(((*str) + len.t_numlen), flags.zero, len.w_padlen);
}

char			*create_dec_string(t_flags flags, t_length len, long long num)
{
	char	*str;
	char	*num_str;
	t_index	index;

	str = ft_calloc((len.total_len + 1), sizeof(char));
	num_str = (flags.conv == 'u' ? itoa_b_uns(num, 10) : itoa_b(num, 10));
	if (!str || !num_str)
		return (NULL);
	flags.zero = ((flags.prec == -1 && flags.zero == 1) ? '0' : ' ');
	fill_width(flags, len, &index, &str);
	ft_memset((str + index.i), '0', len.p_padlen);
	index.i += len.p_padlen;
	if (flags.conv == 'u')
		index.j = 0;
	else
		index.j = ((len.sign == '-') ? 1 : 0);
	if (flags.apo == 1)
		str = set_separators(num, len, str, index.i);
	if (!(flags.prec == 0 && num == 0))
		set_num(str, num_str, &index);
	free(num_str);
	if (flags.minus == 1)
		index.i += len.w_padlen;
	str[index.i] = '\0';
	return (str);
}
