# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: sam <sam@student.codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2020/05/27 13:25:35 by samkortekaa   #+#    #+#                  #
#    Updated: 2020/06/18 17:04:12 by sam           ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRCS = builtins/cd.c \
	    builtins/echo.c \
	    builtins/env.c \
	    builtins/exit.c \
	    builtins/export.c \
	    builtins/pwd.c \
	    builtins/unset.c \
	    utils/lexer_utils.c \
	    utils/linkedlist_utils.c \
		utils/other_utils.c \
		utils/free_utils.c \
	    check_path.c \
	    execute.c \
	    lexer.c \
	    parser.c \
	    shell.c \
	    pipe.c
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
