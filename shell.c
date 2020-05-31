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

int	parse_input(char *str)
{
	char *command[3];
	char **input;
	int i;
	int j;

	input = ft_split(str);
	i = 0;
	command[0] = "pwd";
	command[1] = "cd";
	command[2] = "weekend";
	j = 0;
	while(input[j])
	{
		i = 0;
		while (i < 2)
		{
			if (compare_input(input[j], command[i]) == 0)
				return (i) ;
			i++;
		}
		j++;
	}
	return (-1);
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
	if (i == 0)
		pwd_command();
	if (i == 1)
		write(1, "cd\n", 3);
	if (i == 2)
		write(1, "BIJNA WEEKEND\n", 14);
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
		path(ret);
	}
	return 0;
}

	// TODO: Turn off ctrl-c / ctrl-z / ctrl-d to prevent user exiting shell
		// TODO: lexic analysis
		// TODO: Parse result of lexic analysis into "syntax tree/command table"
		// TODO: Execute "syntax tree/command table"
	// TODO: free everything