# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: skorteka <skorteka@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/05/27 13:25:35 by samkortekaa   #+#    #+#                  #
#    Updated: 2020/07/03 14:32:11 by skorteka      ########   odam.nl          #
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
	    utils/lexer_extract_utils.c \
	    utils/linkedlist_utils.c \
		utils/other_utils.c \
		utils/free_utils.c \
		utils/export_utils.c \
		utils/pipe_utils.c \
	    check_path.c \
	    execute.c \
	    lexer.c \
	    parser.c \
	    pipe.c \
		redirection.c \
		minishell.c \
	    expand.c
CC = gcc
CFLAGS = -I. -Wall -Werror -Wextra -g
ASANCFLAGS = -I. -Wall -Werror -Wextra -g -fsanitize=address -O1 -fno-omit-frame-pointer
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	cd libft && make
	cd libft/printf && make
	cp ./libft/printf/libftprintf.a ./libft.a
	$(CC) $(CFLAGS) -I. -L. -lft $(SRCS) -o $(NAME)

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
	rm -f *.o
	rm -f minishell

re: fclean all
