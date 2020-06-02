/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: merelmourik <merelmourik@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/29 11:46:04 by merelmourik   #+#    #+#                 */
/*   Updated: 2020/06/02 09:43:00 by merelmourik   ########   odam.nl         */
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

	size = pathconf(".", _PC_PATH_MAX);
	path = malloc(sizeof(char) * (size + 1));
	write(1, getcwd(path, size), size);
	write(1, "\n", 1);
	return ;
}

void	path(int i)
{
	// printf("%d\n", i);
	if (i == 0)
		pwd_command();
	if (i == 1)
		write(1, "cd\n", 3);
	if (i == 2)
		write(1, "BIJNA WEEKEND\n", 14);
	return ;
}

int	parse_input(char *str)
{
	char *command[3];
	char **input;
	int i;
	int j;
	int ret;
	int count;

	count = word_count(str);
	input = ft_split(str);
	i = 0;
	command[0] = "pwd";
	command[1] = "cd";
	command[2] = "weekend";
	j = 0;
	while(j < count)
	{
		i = 0;
		while (i <= 2)
		{
			ret = compare_input(input[j], command[i]);
			if (ret == 0)
			{
				path(i);
				i = 3;
				j++;
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
	return 0;
}