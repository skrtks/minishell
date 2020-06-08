# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: skorteka <skorteka@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/05/27 13:25:35 by samkortekaa   #+#    #+#                  #
<<<<<<< HEAD
#    Updated: 2020/06/06 15:34:34 by skorteka      ########   odam.nl          #
=======
#    Updated: 2020/06/06 15:43:37 by mmourik       ########   odam.nl          #
>>>>>>> pwd
#                                                                              #
# **************************************************************************** #

NAME = minishell
<<<<<<< HEAD
SRCS = shell.c lexer.c lexer_utils.c parser.c cd.c env.c
=======
SRCS = shell.c lexer.c lexer_utils.c parser.c pwd.c env.c
>>>>>>> pwd
CC = gcc
CFLAGS = -I. -Wall -Werror -Wextra
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	cd libft && make
	cd libft/printf && make
	cp ./libft/printf/libftprintf.a ./libft.a
	$(CC) -I. -g -L. -lft $(SRCS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean fclean re all

clean:
	cd libft && make clean
	$(RM) $(OBJS)

fclean: clean
	cd libft && make fclean
	cd libft/printf && make fclean
	rm -f libft.a
	$(RM) $(NAME)

re: fclean all
