/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   s_print.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <skorteka@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/11 13:22:39 by skorteka      #+#    #+#                 */
/*   Updated: 2020/06/05 15:28:10 by skorteka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "printf.h"
#include <stdarg.h>
#include <unistd.h>

static int	print_width_prec(t_flags flags, char *str, int len)
{
	char *width;

	if (flags.minus == 1)
		write(1, str, len);
	if (flags.width != -1 && (flags.width - len + 1) > 0)
	{
		width = malloc((flags.width - len + 1) * sizeof(char));
		if (!width)
			return (-1);
		width[flags.width - len] = '\0';
		ft_memset(width, ' ', flags.width - len);
		ft_putstr_fd(width, 1);
		free(width);
	}
	if (flags.minus == -1)
		write(1, str, len);
	return ((flags.width != -1 && (flags.width - len + 1) > 0) ?
			flags.width : len);
}

int			s_print(va_list args, t_flags flags)
{
	char	*str;
	int		len;

	str = va_arg(args, char*);
	if (str == NULL)
		str = "(null)";
	len = ft_strlen(str);
	if (flags.prec != -1)
		len = (flags.prec > len ? len : flags.prec);
	if (flags.width == -1 && flags.prec == -1)
	{
		ft_putstr_fd(str, 1);
		return (len);
	}
	else
		return (print_width_prec(flags, str, len));
}
