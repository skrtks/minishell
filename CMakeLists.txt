cmake_minimum_required(VERSION 3.16)
project(minishell C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(libft)
include_directories(libft/printf)
add_subdirectory(libft)
add_subdirectory(libft/printf)

add_executable(minishell
        cd.c
        cd.h
        env.c
        lexer.c
        lexer.h
        lexer_utils.c
        parser.c
        parser.h
        pwd.c
        shell.c
        shell.h)

target_link_libraries(minishell PUBLIC libft printf)