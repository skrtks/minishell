/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/14 10:49:38 by merelmourik   #+#    #+#                 */
/*   Updated: 2020/07/14 11:06:45 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils/utils.h"

void	sig_handler_inp(int i)
{
	(void)i;
	ft_printf("\nminishell> $ ");
	return ;
}

void	sig_handler(int i)
{
	(void)i;
	ft_printf("\n");
	return ;
}

void	set_signal(void)
{
	signal(SIGQUIT, sig_handler_inp);
	signal(SIGINT, sig_handler_inp);
	signal(SIGSTOP, sig_handler_inp);
}
