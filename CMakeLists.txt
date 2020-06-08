cmake_minimum_required(VERSION 3.16)
project(minishell)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(minishell
        cd.c
        cd.h
        env.c
        lexer.c
        lexer.h
        lexer_utils.c
        libft.a
        parser.c
        parser.h
        pwd.c
        shell.c
        shell.h)
