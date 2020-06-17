cmake_minimum_required(VERSION 3.16)
project(minishell C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(libft)
include_directories(libft/printf)
add_subdirectory(libft)
add_subdirectory(libft/printf)

add_executable(minishell
        builtins/cd.c
        builtins/echo.c
        builtins/env.c
        builtins/exit.c
        builtins/export.c
        builtins/pwd.c
        builtins/unset.c
        utils/lexer_utils.c
        utils/linkedlist_utils.c
        check_path.c
        execute.c
        lexer.c
        parser.c
        shell.c
        execute.h
        lexer.h
        parser.h)

target_link_libraries(minishell PUBLIC libft printf)
