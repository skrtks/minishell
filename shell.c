/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/29 11:46:04 by merelmourik   #+#    #+#                 */
/*   Updated: 2020/06/02 10:06:01 by merelmourik   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		compare_input(char *input, char *command)
{
	int i;

	i = 0;
	while (input[i])
	{
		if (input[i] != command[i])
			return (-1);
		i++;
	}
	if (command[i] != '\0')
		return (-1);
	return (0);
}

void	pwd_command(void)
{
	size_t size;
	char *path;

	size = pathconf(".", _PC_PATH_MAX);		//size has value of 1024
	path = malloc(sizeof(char) * (size + 1));
	if (!path)
		return ;				//errormelding maken
	write(1, getcwd(path, size), size);
	write(1, "\n", 1);
	return ;
}

void	path(int i)
{
	if (i == 0)
		pwd_command();
	if (i == 1)
		write(1, "cd\n", 3);
	if (i == 2)
		write(1, "BIJNA WEEKEND\n", 14);
	return ;
}

char	**command_list(char **command)
{
	command = (char **) malloc(sizeof(char*) * (3));
	if (!command)
		return (NULL);
	command[0] = "pwd";
	command[1] = "cd";
	command[2] = "weekend";
	return(command);
}

int	parse_input(char *str)
{
	char **command;
	char **input;
	int i;

	input = ft_split(str);
	if (input == NULL)
		return (-2);			//errormelding maken
	command = command_list(command);
	if (input == NULL)
		return (-2);			//errormelding maken
	i = 0;
	while (*input)
	{
		i = 0;
		while (i <= 2)
		{
			if (compare_input(*input, command[i]) == 0)
			{
				path(i);
				i = 3;
				input++;
			}
			i++;
			if (i == 3)
				return (-1);
		}
	}
	return (0);
}


int main(void)
{
	int   	ret;
	char	*input;
	
	while (1)
	{
		write(1, "minishell> $ ", 13);
		ret = next_line(0, &input);
		if (ret == -1)
		{
			errno = 0;
			break ;
		}
		ret = parse_input(input);
		if (ret == -1)
			write(1, "unrecognised input.\n", 20);
	}
	return (0);
}