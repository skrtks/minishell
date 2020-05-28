# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: samkortekaas <samkortekaas@student.codam.nl> +#+                      #
#                                                    +#+                       #
#    Created: 2020/05/27 13:25:35 by samkortekaas  #+#    #+#                  #
#    Updated: 2020/05/27 14:03:45 by samkortekaas  ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

SRCS = test.c
CC = gcc
CFLAGS = -I. -Wall -Werror -Wextra
NAME = minishell
OBJS := $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	cd libft && make
	cp ./libft/libft.a .
	$(CC) -I. -g -L. -lft $(SRCS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

asan: $(OBJS) $(NAME)
	$(CC) $(CFLAGS) -fsanitize=address -O1 -fno-omit-frame-pointer \
	-g -L. -lftprintf $(SRCS) main.c -o printf

.PHONY: clean fclean re all test

clean:
	cd libft && make clean
	-rm -f $(OBJS)

fclean: clean
	cd libft && make fclean
	-rm -f $(NAME)
	-rm -f printf
	-rm -rf printf.dSYM/

re: fclean all
