cmake_minimum_required(VERSION 3.15.3)
project(minishell C)

set(CMAKE_C_STANDARD 11)
#SET(CMAKE_C_FLAGS "-g -fprofile-instr-generate -fcoverage-mapping")
#set(CMAKE_C_FLAGS "-g -fsanitize=address -O1 -fno-omit-frame-pointer")

include_directories(.)
include_directories(libft)
include_directories(libft/printf)
add_subdirectory(libft)
add_subdirectory(libft/printf)

add_executable(minishell
		builtins/builtins.h
		builtins/cd.c
		builtins/echo.c
		builtins/env.c
		builtins/exit.c
		builtins/export.c
		builtins/pwd.c
		builtins/unset.c
		utils/export_utils.c
		utils/free_utils.c
		utils/lexer_utils.c
		utils/linkedlist_utils.c
		utils/other_utils.c
		utils/pipe_utils.c
		utils/utils.h
		utils/expand_utils.c
        utils/check_path.c
        utils/execute.c
        lexer.c
        minishell.h
        parser.c
        minishell.c
        pipe.c
		utils/expand.c
		redirection.c
		utils/check.c)

target_link_libraries(minishell PUBLIC libft printf)
