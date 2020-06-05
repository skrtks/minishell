/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printf.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: skorteka <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/11 09:30:56 by skorteka      #+#    #+#                 */
/*   Updated: 2019/12/11 09:31:00 by skorteka      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H
# include <stdarg.h>
# include <unistd.h>

typedef struct		s_flags
{
	int				minus;
	int				zero;
	int				hash;
	int				apo;
	int				space;
	int				plus;
	int				width;
	int				prec;
	int				l_mod;
	char			conv;
}					t_flags;

typedef struct		s_length {
	int				numlen;
	int				p_numlen;
	int				t_numlen;
	int				p_padlen;
	int				w_padlen;
	int				total_len;
	char			sign;
}					t_length;

typedef struct		s_index {
	int				i;
	int				j;
}					t_index;

int					ft_printf(const char *format, ...);
int					c_print(va_list args, t_flags flags);
int					s_print(va_list args, t_flags flags);
int					i_print(va_list args, t_flags flags);
int					x_print(va_list args, t_flags flags);
int					p_print(va_list args, t_flags flags);
int					u_print(va_list args, t_flags flags);

int					int_length(long long n);
char				*set_case(char *str, t_flags flags);
int					set_string(char **dst, char *src, int i);
t_flags				init_flags(void);
int					sep_calculator(long long num);
char				*set_separators(long long num, t_length len, char *str,
									int start);
char				*set_num(char *str, char *num_str,
							t_index *index);
char				*create_dec_string(t_flags flags, t_length len,
										long long num);
t_flags				parse_l_mod(const char **format, t_flags flags);
long long			get_dec(t_flags flags, va_list args);
unsigned long long	get_dec_uns(t_flags flags, va_list args);
char				*itoa_b(long long value, int base);
char				*itoa_b_uns(unsigned long long value, int base);
t_flags				parse_starwidth(t_flags flags, va_list args);
int					free_va_end(va_list args);

#endif
