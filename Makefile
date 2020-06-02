# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: samkortekaas <samkortekaas@student.codam.nl> +#+                      #
#                                                    +#+                       #
#    Created: 2020/05/27 13:25:35 by samkortekaa   #+#    #+#                  #
#    Updated: 2020/06/02 15:24:59 by samkortekaas  ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRCS = shell.c next_line.c lexer.c
CC = gcc
CFLAGS = -I. -Wall -Werror -Wextra
OBJs = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	cd libft && make
	cp ./libft/libft.a ./libft.a
	$(CC) -I. -g -L. -lft $(SRCS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	cd libft && make clean
	$(RM) $(OBJS)

fclean: clean
	cd libft && make fclean
	rm -f libft.a
	$(RM) $(NAME)

re: fclean all
