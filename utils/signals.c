/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/09 20:32:18 by merelmourik   #+#    #+#                 */
/*   Updated: 2020/07/13 16:09:50 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils/utils.h"
#include <signal.h>

void	sig_handler_inp(int _)
{
	(void)_;
	ft_printf("\nminishell> $ ");
	return ;
}

void	sig_handler(int _)
{
	(void)_;
	ft_printf("\n");
	return ;
}

void	set_signal(void)
{
	signal(SIGQUIT, sig_handler_inp);
	signal(SIGINT, sig_handler_inp);
	signal(SIGSTOP, sig_handler_inp);
}
