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
        utils/free_utils.c
        utils/lexer_utils.c
        utils/linkedlist_utils.c
        utils/other_utils.c
        utils/utils.h
        check_path.c
        execute.c
        execute.h
        lexer.c
        lexer.h
        parser.c
        parser.h
        shell.c)

target_link_libraries(minishell PUBLIC libft printf)
