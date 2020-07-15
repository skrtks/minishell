# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: merelmourik <merelmourik@student.42.fr>      +#+                      #
#                                                    +#+                       #
#    Created: 2020/05/27 13:25:35 by samkortekaa   #+#    #+#                  #
#    Updated: 2020/07/15 10:28:51 by merelmourik   ########   odam.nl          #
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
		utils/check.c \
	    utils/check_path.c \
	    utils/execute.c \
	    utils/expand.c \
	    utils/lexer_utils.c \
		utils/expand_utils.c \
		utils/export_utils.c \
		utils/free_utils.c \
		utils/signals.c \
	    utils/linkedlist_utils.c \
		utils/other_utils.c \
		utils/pipe_utils.c \
	    lexer.c \
	    parser.c \
	    pipe.c \
		redirection.c \
		minishell.c
CC = gcc
CFLAGS = -I. -Wall -Werror -Wextra -g
AS = -I. -Wall -Werror -Wextra -g -fsanitize=address -O1 -fno-omit-frame-pointer
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "start..."
	@echo ">> compiling libft"
	@cd libft && make
	@echo ">> compiling printf"
	@cd libft/printf && make
	@cp ./libft/printf/libftprintf.a ./libft.a
	@echo "+ linking"
	@$(CC) $(CFLAGS) -I. -L. -lft $(SRCS) -o $(NAME)
	@echo "Done"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean fclean re all

clean:
	@echo ">> Cleaning..."
	@cd libft && make clean
	@cd libft/printf && make clean
	@$(RM) $(OBJS)

fclean: clean
	@cd libft && make fclean
	@cd libft/printf && make fclean
	@rm -f libft.a
	@rm -f *.o
	@rm -f minishell
	@rm -rf minishell.dSYM

re: fclean all
