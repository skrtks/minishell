# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: merelmourik <merelmourik@student.42.fr>      +#+                      #
#                                                    +#+                       #
#    Created: 2019/12/11 09:32:11 by skorteka      #+#    #+#                  #
#    Updated: 2020/07/14 14:33:37 by merelmourik   ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

SRCS = utils_1.c utils_2.c utils_3.c ft_itoa_base.c\
		p_print.c x_print.c u_print.c s_print.c i_print.c printf.c
CC = gcc
CFLAGS = -I. -Wall -Werror -Wextra
NAME = libftprintf.a
OBJS := $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@cp ../libft.a ./$(NAME)
	@ar rc $@ $^
	@cp libftprintf.a ../../libft.a

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

bonus: $(NAME)

test: $(OBJS) $(NAME)
	$(CC) -I. -g -L. -lftprintf $(SRCS) main.c -o printf

asan: $(OBJS) $(NAME)
	$(CC) $(CFLAGS) -fsanitize=address -O1 -fno-omit-frame-pointer \
	-g -L. -lftprintf $(SRCS) main.c -o printf

.PHONY: clean fclean re all test

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f *.o
	@rm -f $(NAME)
	@rm -f printf
	@rm -rf printf.dSYM/

re: fclean all
