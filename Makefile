# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: sam <sam@student.codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2020/05/27 13:25:35 by samkortekaa   #+#    #+#                  #
#    Updated: 2020/06/12 12:16:30 by sam           ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRCS = shell.c lexer.c lexer_utils.c parser.c cd.c env.c pwd.c echo.c export.c\
	env_utils.c exit.c execute.c
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
