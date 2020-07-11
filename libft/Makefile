# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: sam <sam@student.codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2019/10/29 10:06:20 by skorteka      #+#    #+#                  #
#    Updated: 2020/06/20 15:46:47 by sam           ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

SRCS = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
	ft_isdigit.c ft_isprint.c ft_memccpy.c ft_memchr.c ft_memcmp.c \
	ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c ft_strrchr.c \
	ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c \
	ft_tolower.c ft_toupper.c ft_calloc.c ft_strdup.c ft_substr.c \
	ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
	ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
	ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c get_next_line.c \
	get_next_line_utils.c ft_stroll.c
CC = gcc
CFLAGS = -I. -Wall -Werror -Wextra
OBJS := $(SRCS:.c=.o)
NAME = libft.a

all: $(NAME)

$(NAME): $(OBJS)
	@ar rc $@ $^

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean fclean re all

clean:
	@-rm -f $(OBJS)

fclean: clean
	@rm -f libft.a
	@rm -f *.o
	@rm -f $(NAME)

re: fclean all
